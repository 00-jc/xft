/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_resample.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 14:31:33 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_tailor.h>

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
static inline void	xft_finalmix(t_tailor_job *j, t_u64a *medians,
	t_u64a hilo[2], t_plankb plan)
{
	t_qsort_ctx	ctx;

	ctx = (t_qsort_ctx){(t_u8 *)&j->swap, sizeof(t_u64a), xft_cmp_u64};
	xft_qsort((t_any)medians, &ctx, 0, plan.b);
	hilo[0] = medians[(plan.b * 25) / 1000];
	hilo[1] = medians[(plan.b * 975) / 1000];
}

__attribute__((__nonnull__(1, 3), __always_inline__))
static inline t_result	xft_bootstrap_ci(t_tailor_job *j, t_buffer surv,
	t_u64a hilo[2], t_plankb plan)
{
	t_u64a				*medres[2];
	t_xoshiro			xo;
	const t_u64a		*src;
	t_size				ij[2];
	t_qsort_ctx			ctx;

	if (surv.mem == nullptr)
		__builtin_unreachable();
	medres[0] = xft_arena_alloc(j->arena, sizeof(t_u64a) * plan.b, 64);
	medres[1] = xft_arena_alloc(j->arena, sizeof(t_u64a) * surv.size, 64);
	if (__builtin_expect(medres[0] == nullptr || medres[1] == nullptr, 0))
		return (KO);
	xft_xoshiro_init(xo);
	src = (const t_u64a *)surv.mem;
	ctx = (t_qsort_ctx){(t_u8 *)&j->swap, sizeof(t_u64a), xft_cmp_u64};
	ij[0] = 0;
	while (ij[0] < plan.b)
	{
		ij[1] = 0;
		while (ij[1] < surv.size)
			medres[1][ij[1]++] = src[xft_xoshiro256ss(xo) % surv.size];
		xft_qsort((t_any)medres[1], &ctx, 0, surv.size);
		medres[0][ij[0]++] = medres[1][surv.size >> 1];
	}
	return (xft_finalmix(j, medres[0], hilo, plan), OK);
}

__attribute__((__nonnull__(1)))
t_result	xft_bootstrap(t_tailor_job *j, t_buffer surv, t_plankb plan)
{
	t_u64a			hilo[2];
	t_qsort_ctx		ctx;

	if (surv.mem == nullptr)
		__builtin_unreachable();
	if (__builtin_expect(xft_bootstrap_ci(j, surv, hilo, plan) == KO, 0))
		return (KO);
	ctx = (t_qsort_ctx){(t_u8 *)&j->swap, sizeof(t_u64a), xft_cmp_u64};
	xft_qsort(surv.mem, &ctx, 0, surv.size);
	j->result.med = ((t_blk64ra)surv.mem)[surv.size >> 1] / plan.dp.iters;
	j->result.min = ((t_blk64ra)surv.mem)[0] / plan.dp.iters;
	j->result.lo = hilo[0] / plan.dp.iters;
	j->result.hi = hilo[1] / plan.dp.iters;
	return (OK);
}
