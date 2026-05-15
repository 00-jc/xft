/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_resample.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 23:40:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 11:18:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tailor.h"
#include "io.h"
#include "private/ft_p_math.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline void	ft_finalmix(t_u64a *medians, t_u64a hilo[2],
	t_plankb plan)
{
	t_qsort_ctx	ctx;
	t_u64a		swap;

	ctx = (t_qsort_ctx){(t_u8 *)&swap, sizeof(t_u64a), ft_cmp_u64};
	ft_qsort((void *)medians, &ctx, 0, plan.b);
	hilo[0] = medians[(plan.b * 25) / 1000];
	hilo[1] = medians[(plan.b * 975) / 1000];
}

__attribute__((__nonnull__(1, 3), __always_inline__))
static inline int	ft_bootstrap_ci(t_tailor *t, t_buffer surv, t_u64a hilo[2],
	t_plankb plan)
{
	t_u64a				*medres[2];
	t_xoshiro			xo;
	t_perf_sample		*src;
	size_t				ij[2];
	t_qsort_ctx			ctx;

	if (surv.mem == nullptr)
		__builtin_unreachable();
	medres[0] = ft_arena_alloc(&t->arena, sizeof(t_u64a) * plan.b, 64);
	medres[1] = ft_arena_alloc(&t->arena, sizeof(t_u64a) * surv.size, 64);
	if (__builtin_expect(medres[0] == nullptr || medres[1] == nullptr, 0))
		return (0);
	ft_xoshiro_init(xo);
	src = (t_perf_sample *)surv.mem;
	ctx = (t_qsort_ctx){(t_u8 *)&t->swap, sizeof(t_u64a), ft_cmp_u64};
	ij[0] = 0;
	while (ij[0] < plan.b)
	{
		ij[1] = 0;
		while (ij[1] < surv.size)
			medres[1][ij[1]++] = src[ft_xoshiro256ss(xo) % surv.size].ns;
		ft_qsort((void *)medres[1], &ctx, 0, surv.size);
		medres[0][ij[0]++] = medres[1][surv.size >> 1];
	}
	return (ft_finalmix(medres[0], hilo, plan), 1);
}

__attribute__((__nonnull__(1, 3, 4)))
static inline int	ft_getpost_med(t_tailor *t, t_buffer surv,
	t_u64a *med, t_u64a *min)
{
	t_u64a			m;
	t_u64a			*arr;
	t_perf_sample	*src;
	size_t			i;
	t_qsort_ctx		ctx;

	if (surv.mem == nullptr)
		__builtin_unreachable();
	arr = ft_arena_alloc(&t->arena, sizeof(t_u64a) * surv.size, 64);
	if (__builtin_expect(arr == nullptr, 0))
		return (0);
	src = (t_perf_sample *)surv.mem;
	i = 0;
	m = src[0].ns;
	while (i < surv.size)
	{
		arr[i] = src[i].ns;
		m = ft_tern(src[i].ns < m, src[i].ns, m);
		++i;
	}
	ctx = (t_qsort_ctx){(t_u8 *)&t->swap, sizeof(t_u64a), ft_cmp_u64};
	ft_qsort((void *)arr, &ctx, 0, surv.size);
	*med = arr[surv.size >> 1];
	*min = m;
	return (1);
}

__attribute__((__nonnull__(1)))
int	ft_bootstrap(t_tailor *t, t_buffer surv, t_plankb plan, t_blk8r name)
{
	t_u64a	hilo[2];
	t_u64a	med;
	t_u64a	min;

	__attribute__((assume(surv.mem != nullptr)));
	if (__builtin_expect(ft_bootstrap_ci(t, surv, hilo, plan) == 0, 0))
		return (0);
	if (__builtin_expect(ft_getpost_med(t, surv, &med, &min) == 0, 0))
		return (0);
	ft_print_summary(surv, plan, name, (t_u64a[4]){med, min, hilo[0], hilo[1]});
	return (1);
}
