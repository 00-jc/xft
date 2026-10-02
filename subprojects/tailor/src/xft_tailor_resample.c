/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_resample.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 14:31:33 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_tailor.h"
#include "io.h"
#include "xft_p_math.h"
#include "tailor.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline void	xft_finalmix(t_u64a *medians, t_u64a hilo[2],
	t_plankb plan)
{
	t_qsort_ctx	ctx;
	t_u64a		swap;

	ctx = (t_qsort_ctx){(t_u8 *)&swap, sizeof(t_u64a), xft_cmp_u64};
	xft_qsort((t_any)medians, &ctx, 0, plan.b);
	hilo[0] = medians[(plan.b * 25) / 1000];
	hilo[1] = medians[(plan.b * 975) / 1000];
}

__attribute__((__nonnull__(1, 3), __always_inline__))
static inline t_result	xft_bootstrap_ci(t_tailor *t, t_buffer surv,
	t_u64a hilo[2], t_plankb plan)
{
	t_u64a				*medres[2];
	t_xoshiro			xo;
	t_perf_sample		*src;
	t_size				ij[2];
	t_qsort_ctx			ctx;

	if (surv.mem == nullptr)
		__builtin_unreachable();
	medres[0] = xft_arena_alloc(&t->arena, sizeof(t_u64a) * plan.b, 64);
	medres[1] = xft_arena_alloc(&t->arena, sizeof(t_u64a) * surv.size, 64);
	if (__builtin_expect(medres[0] == nullptr || medres[1] == nullptr, 0))
		return (KO);
	xft_xoshiro_init(xo);
	src = (t_perf_sample *)surv.mem;
	ctx = (t_qsort_ctx){(t_u8 *)&t->swap, sizeof(t_u64a), xft_cmp_u64};
	ij[0] = 0;
	while (ij[0] < plan.b)
	{
		ij[1] = 0;
		while (ij[1] < surv.size)
			medres[1][ij[1]++] = src[xft_xoshiro256ss(xo) % surv.size].ns;
		xft_qsort((t_any)medres[1], &ctx, 0, surv.size);
		medres[0][ij[0]++] = medres[1][surv.size >> 1];
	}
	return (xft_finalmix(medres[0], hilo, plan), OK);
}

__attribute__((__nonnull__(1, 3, 4)))
static inline t_result	xft_getpost_med(t_tailor *t, t_buffer surv,
	t_u64a *med, t_u64a *min)
{
	t_u64a			m;
	t_u64a			*arr;
	t_perf_sample	*src;
	t_size			i;
	t_qsort_ctx		ctx;

	if (surv.mem == nullptr)
		__builtin_unreachable();
	arr = xft_arena_alloc(&t->arena, sizeof(t_u64a) * surv.size, 64);
	if (__builtin_expect(arr == nullptr, 0))
		return (KO);
	src = (t_perf_sample *)surv.mem;
	i = 0;
	m = src[0].ns;
	while (i < surv.size)
	{
		arr[i] = src[i].ns;
		m = xft_tern(src[i].ns < m, src[i].ns, m);
		++i;
	}
	ctx = (t_qsort_ctx){(t_u8 *)&t->swap, sizeof(t_u64a), xft_cmp_u64};
	xft_qsort((t_any)arr, &ctx, 0, surv.size);
	*med = arr[surv.size >> 1];
	*min = m;
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	xft_bootstrap(t_tailor *t, t_buffer surv,
	t_plankb plan, t_blk8r name)
{
	t_u64a	hilo[2];
	t_u64a	med;
	t_u64a	min;

	__attribute__((assume(surv.mem != nullptr)));
	if (__builtin_expect(xft_bootstrap_ci(t, surv, hilo, plan) == KO, 0))
		return (KO);
	if (__builtin_expect(xft_getpost_med(t, surv, &med, &min) == KO, 0))
		return (KO);
	xft_print_summary(surv, plan, (t_tailor_report_ctx){name, &t->writer},
		(t_u64a[4]){med, min, hilo[0], hilo[1]});
	return (OK);
}
