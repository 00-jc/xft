/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_run.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 16:47:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_tailor.h>

__attribute__((__nonnull__(1)))
t_result	xft_tailor_prepare(t_tailor_job *j)
{
	j->plan = xft_get_kb(j);
	j->soa = xft_new_soa(xft_arena_allocator(j->arena), j->plan.k_runs,
			xft__tailor_ctx());
	if (__builtin_expect(j->soa.ptr == nullptr, 0))
		return (KO);
	j->arg = (t_tailor_arg){.iters = j->plan.dp.iters, .buffers = j->buffers};
	xft_xoshiro_init(j->arg.xoshiro);
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	xft_tailor_sample(t_tailor_job *j)
{
	t_tailor_arg	arg;
	t_perf_sample	s;

	if (j->soa.occupied_elements >= j->plan.k_runs)
		return (OK);
	arg = j->arg;
	xft_perf_start_sample(j->counters, &s);
	j->fn(&arg);
	if (__builtin_expect(!xft_perf_collect_sample(arg.iters, j->counters, &s),
			0))
		return (KO);
	j->arg = arg;
	xft_soa_append_from_struct_unchecked(&j->soa, &s, xft__tailor_ctx());
	return (OK);
}

__attribute__((__nonnull__(1, 4), __always_inline__))
static inline void	xft_calc_mad(t_tailor_job *j, t_buffer scratch, t_u64a med,
	t_u64a *mad)
{
	t_size					i;
	t_u64a					tmp;
	t_qsort_ctx				ctx;

	i = 0;
	if (scratch.mem == nullptr)
		__builtin_unreachable();
	while (i < scratch.size)
	{
		tmp = ((t_blk64ra)scratch.mem)[i];
		((t_blk64w)scratch.mem)[i] = xft_tern(tmp < med, med - tmp, tmp - med);
		++i;
	}
	ctx = (t_qsort_ctx){(t_u8 *)&j->swap, sizeof(t_u64a), xft_cmp_u64};
	xft_qsort((t_any)scratch.mem, &ctx, 0, scratch.size);
	*mad = ((t_blk64ra)scratch.mem)[scratch.size >> 1];
}

__attribute__((__nonnull__(1, 3), __always_inline__))
static inline t_result	xft_calc(t_tailor_job *j, t_buffer ns, t_u64a *medmad)
{
	t_u64a					*arr;
	t_qsort_ctx				ctx;

	if (ns.mem == nullptr)
		__builtin_unreachable();
	arr = xft_arena_alloc(j->arena, sizeof(t_u64a) * ns.size, 64);
	if (__builtin_expect(arr == nullptr, 0))
		return (KO);
	xft_memcpy(arr, ns.mem, sizeof(t_u64a) * ns.size);
	ctx = (t_qsort_ctx){(t_u8 *)&j->swap, sizeof(t_u64a), xft_cmp_u64};
	xft_qsort((t_any)arr, &ctx, 0, ns.size);
	medmad[0] = arr[ns.size >> 1];
	xft_calc_mad(j, xft_fatptr((t_any)arr, ns.size), medmad[0], medmad + 1);
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	xft_tailor_finish(t_tailor_job *j)
{
	t_buffer	surv;
	t_u64a		medmad[2];

	j->plan.dp.bytes_processed = j->arg.bytes_processed;
	surv = xft_fatptr((t_u8 *)((t_u64a *)xft_soa_fields(&j->soa,
					xft__tailor_ctx(), TAILOR_NS) + K_WARMUP),
			j->soa.occupied_elements - K_WARMUP);
	if (__builtin_expect(xft_calc(j, surv, medmad) == KO, 0))
		return (KO);
	medmad[1] = xft_tern(medmad[1] == 0, 1, medmad[1]);
	surv = xft_tailor_survivors(j, &j->soa,
			medmad[0] + (medmad[1] * 7413ULL) / 1000ULL, j->plan);
	if (__builtin_expect(surv.mem == nullptr, 0))
		return (KO);
	return (xft_bootstrap(j, surv, j->plan));
}
