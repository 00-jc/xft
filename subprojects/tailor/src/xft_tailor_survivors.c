/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_survivors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_tailor.h>
#include <xft/math.h>

__attribute__((const, __always_inline__, __returns_nonnull__, __used__))
inline const t_soa_context	*xft__tailor_ctx(void)
{
	__extension__ static const t_soa_context	ctx = {
		.total_struct_size = TAILOR_COLS * sizeof(t_u64a),
		.max_alignment = sizeof(t_u64a), .fields_count = TAILOR_COLS,
		.entries = {
	{8, __builtin_offsetof(t_perf_sample, ns), 0},
	{8, __builtin_offsetof(t_perf_sample, n), 8},
	{8, __builtin_offsetof(t_perf_sample, cache_ll), 16},
	{8, __builtin_offsetof(t_perf_sample, cache_miss), 24},
	{8, __builtin_offsetof(t_perf_sample, cycles), 32},
	{8, __builtin_offsetof(t_perf_sample, instr), 40},
	{8, __builtin_offsetof(t_perf_sample, branches), 48},
	{8, __builtin_offsetof(t_perf_sample, branch_miss), 56},
	{8, __builtin_offsetof(t_perf_sample, alignment_faults), 64},
	{8, __builtin_offsetof(t_perf_sample, page_faults), 72},
	}};

	return (&ctx);
}

__attribute__((__nonnull__(1, 3), __always_inline__))
static inline void	xft__tailor_sums(const t_soa *soa, t_u64a threshold,
	t_u64a *sums)
{
	const t_u64a	*ns = xft_soa_fields(soa, xft__tailor_ctx(), TAILOR_NS);
	const t_u64a	*col;
	t_size			c;
	t_size			i;

	c = 0;
	while (c < TAILOR_COLS)
	{
		col = xft_soa_fields(soa, xft__tailor_ctx(), c);
		sums[c] = 0;
		i = K_WARMUP;
		while (i < soa->occupied_elements)
		{
			sums[c] += xft_tern(ns[i] <= threshold, col[i], 0);
			++i;
		}
		++c;
	}
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline void	xft__tailor_fill(t_tailor_result *r, const t_u64a *sums,
	t_size relevant, t_plankb plan)
{
	const t_f64	calls = (t_f64)relevant * (t_f64)plan.dp.iters;

	r->ns = (t_f64)sums[TAILOR_NS] / calls;
	r->ipc = xft_dtern(sums[TAILOR_CYCLES] != 0, (t_f64)sums[TAILOR_INSTR]
			/ (t_f64)sums[TAILOR_CYCLES], 0.0);
	r->gb_per_sec = xft_dtern(sums[TAILOR_NS] != 0,
			(t_f64)plan.dp.bytes_processed / ((t_f64)plan.k_runs
				* (t_f64)plan.dp.iters) / r->ns, 0.0);
	r->cycles = (t_f64)sums[TAILOR_CYCLES] / calls;
	r->instr = (t_f64)sums[TAILOR_INSTR] / calls;
	r->total_iters = (t_u64a)plan.k_runs * plan.dp.iters;
	r->relevant = relevant;
	r->burst = plan.dp.iters;
	r->resamples = plan.b;
	r->branches = sums[TAILOR_BRANCHES];
	r->branch_miss = sums[TAILOR_BRANCH_MISS];
	r->cache_ll = sums[TAILOR_CACHE_LL];
	r->cache_miss = sums[TAILOR_CACHE_MISS];
	r->alignment_faults = sums[TAILOR_ALIGNMENT_FAULTS];
	r->page_faults = sums[TAILOR_PAGE_FAULTS];
}

__attribute__((__nonnull__(1, 2)))
t_buffer	xft_tailor_survivors(t_tailor_job *j, const t_soa *soa,
	t_u64a threshold, t_plankb plan)
{
	const t_u64a	*ns = xft_soa_fields(soa, xft__tailor_ctx(), TAILOR_NS);
	t_u64a			*surv;
	t_u64a			sums[TAILOR_COLS];
	t_size			i;
	t_size			n;

	surv = xft_arena_alloc(j->arena, sizeof(t_u64a) * soa->occupied_elements,
			64);
	if (__builtin_expect(surv == nullptr, 0))
		return (xft_fatptr(nullptr, 0));
	i = K_WARMUP;
	n = 0;
	while (i < soa->occupied_elements)
	{
		surv[n] = ns[i];
		n += ns[i++] <= threshold;
	}
	xft__tailor_sums(soa, threshold, sums);
	xft__tailor_fill(&j->result, sums, n, plan);
	return (xft_fatptr((t_any)surv, n));
}
