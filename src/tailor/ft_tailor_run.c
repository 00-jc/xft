/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:41:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 11:20:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_tailor.h"

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
static inline t_buffer	ft_tailor_runfn(t_tailor *t, t_tailor_fn fn,
	t_plankb *oplan)
{
	t_plankb		plan;
	t_perf_sample	*samples;
	t_tailor_arg	arg;
	size_t			i;
	t_perf_sample	s;

	plan = ft_get_kb(t, fn);
	t->rpoint = ft_arena_checkpoint(&t->arena);
	samples = ft_arena_alloc(&t->arena, sizeof(*samples) * plan.k_runs, 64);
	if (!samples)
		return (ft_arena_rewind(&t->arena, t->rpoint), (t_buffer){0, 0});
	i = 0;
	(ft_xoshiro_init(arg.xoshiro), (void)(arg.buffers = t->rand_buffers));
	plan.dp.bytes_processed = 0;
	arg.iters = plan.dp.iters;
	while (i < plan.k_runs)
	{
		(ft_perf_start_sample(t->counters, &s), fn(&arg));
		if (!ft_perf_collect_sample(arg.iters, t->counters, &s))
			return (ft_arena_rewind(&t->arena, t->rpoint), (t_buffer){0, 0});
		samples[i++] = s;
	}
	plan.dp.bytes_processed = arg.bytes_processed;
	*oplan = plan;
	return (ft_fatptr((void *)samples, plan.k_runs));
}

__attribute__((__nonnull__(3), __always_inline__))
static inline void	ft_calc_mad(t_buffer scratch, t_u64a med, t_u64a *mad)
{
	size_t					i;
	t_u64a					tmp;
	t_u64a					swap;
	t_qsort_ctx				ctx;

	i = 0;
	if (scratch.mem == nullptr)
		__builtin_unreachable();
	while (i < scratch.size)
	{
		tmp = ((t_blk64ra)scratch.mem)[i];
		((t_blk64w)scratch.mem)[i] = ft_tern(tmp < med, med - tmp, tmp - med);
		++i;
	}
	ctx = (t_qsort_ctx){(t_u8 *)&swap, sizeof(t_u64a), ft_cmp_u64};
	ft_qsort((void *)scratch.mem, &ctx, 0, scratch.size);
	*mad = ((t_blk64ra)scratch.mem)[scratch.size >> 1];
}

__attribute__((__nonnull__(1, 3, 4), __always_inline__))
static inline int	ft_calc(t_tailor *t, t_buffer samples, t_u64a *med,
	t_u64a *mad)
{
	t_u64a					*arr;
	t_arena_checkpoint		c;
	size_t					i;
	t_qsort_ctx				ctx;

	c = ft_arena_checkpoint(&t->arena);
	arr = ft_arena_alloc(&t->arena, sizeof(t_u64a) * samples.size, 64);
	if (!arr)
		return (0);
	i = 0;
	while (i < samples.size)
	{
		arr[i] = ((t_perf_sample *)samples.mem)[i].ns;
		++i;
	}
	ctx = (t_qsort_ctx){(t_u8 *)&t->swap, sizeof(t_u64a), ft_cmp_u64};
	ft_qsort((void *)arr, &ctx, 0, samples.size);
	*med = arr[samples.size >> 1];
	ft_calc_mad(ft_fatptr((void *)arr, samples.size), *med, mad);
	return (ft_arena_rewind(&t->arena, c), 1);
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_buffer	ft_make_surv(t_tailor *t, t_buffer sample,
	t_u64a threshold)
{
	t_perf_sample	*surv;
	t_perf_sample	*src;
	size_t			i;
	size_t			n_surv;

	surv = ft_arena_alloc(&t->arena, sizeof(*surv) * sample.size, 64);
	if (__builtin_expect(surv == nullptr, 0))
		return ((t_buffer){0, 0});
	src = (t_perf_sample *)sample.mem;
	i = 0;
	n_surv = 0;
	while (i < sample.size)
	{
		if (src[i].ns <= threshold)
			surv[n_surv++] = src[i];
		++i;
	}
	return (ft_fatptr((void *)surv, n_surv));
}

__attribute__((__nonnull__(1)))
int	ft_tailor_benchfn(t_tailor *t, t_tailor_fn fn, t_blk8r name)
{
	t_plankb	plan;
	t_buffer	sample;
	t_u64a		threshold;
	t_u64a		medmad[2];

	sample = ft_tailor_runfn(t, fn, &plan);
	if (__builtin_expect(sample.mem == nullptr, 0))
		return (0);
	sample.mem += K_WARMUP * sizeof(t_perf_sample);
	sample.size -= K_WARMUP;
	if (__builtin_expect(ft_calc(t, sample, medmad, medmad + 1) == 0, 0))
		return (ft_arena_rewind(&t->arena, t->rpoint), 0);
	medmad[1] = ft_tern(medmad[1] == 0, 1, medmad[1]);
	threshold = medmad[0] + (medmad[1] * 7413ULL) / 1000ULL;
	sample = ft_make_surv(t, sample, threshold);
	if (__builtin_expect(sample.mem == nullptr, 0))
		return (0);
	ft_bootstrap(t, sample, plan, name);
	ft_arena_rewind(&t->arena, t->rpoint);
	return (1);
}
