/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_summary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:24:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 11:19:35 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "private/ft_p_tailor.h"
#include "macros.h"
#include "io.h"
#include "bmi.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline void	ft_sum_counters(t_perf_sample *src, t_perf_sample *sum,
	t_size n)
{
	t_size	i;

	*sum = (t_perf_sample){0};
	i = 0;
	while (i < n)
	{
		sum->ns += src[i].ns;
		sum->cycles += src[i].cycles;
		sum->instr += src[i].instr;
		sum->cache_miss += src[i].cache_miss;
		sum->cache_ll += src[i].cache_ll;
		sum->branches += src[i].branches;
		sum->branch_miss += src[i].branch_miss;
		sum->alignment_faults += src[i].alignment_faults;
		sum->page_faults += src[i].page_faults;
		++i;
	}
}

static void	ft_print_head(t_perf_sample sum, t_plankb plan, t_blk8r name,
	t_u64a total_iters)
{
	t_f64	bps;

	bps = ft_dtern(sum.ns != 0,
			(t_f64)plan.dp.bytes_processed / (t_f64)sum.ns * 1e9, 0.0) / 1e9;
	ft_printf(ANSI_BCYAN" * %s"ANSI_RESET"\n"
		" ├─ time         = %f ns per_call\n"
		" ├─ ipc          = %f\n"
		" ├─ GB/sec       = %f\n"
		" ├─ cycles       = %f\n"
		" ├─ instr        = %f per_call\n",
		name,
		ft_dtern(total_iters != 0,
			(t_f64)sum.ns / (t_f64)total_iters, (t_f64)0.0),
		ft_dtern(sum.cycles != 0,
			(t_f64)sum.instr / (t_f64)sum.cycles, (t_f64)0.0),
		bps,
		(t_f64)sum.cycles / (t_f64)plan.dp.iters,
		(t_f64)sum.instr / (t_f64)plan.dp.iters);
}

static void	ft_print_tail(t_perf_sample sum)
{
	ft_printf(
		" │\n"
		" ├─ branch miss  = %f%%\n"
		" │  └───────────── total_ratio=%lu/%lu\n"
		" │\n"
		" ├─ LL     miss  = %f%%\n"
		" │  └───────────── total_ratio=%lu/%lu\n"
		" │\n"
		" ├─ align faults = %lu\n"
		" └─ page  faults = %lu\n",
		ft_dtern(sum.branches > 0,
			(t_f64)sum.branch_miss / (t_f64)sum.branches * 100.0, 0.0),
		sum.branch_miss, sum.branches,
		ft_dtern(sum.cache_ll > 0,
			(t_f64)sum.cache_miss / (t_f64)sum.cache_ll * 100.0, 0.0),
		sum.cache_miss, sum.cache_ll,
		sum.alignment_faults, sum.page_faults);
}

__attribute__((__nonnull__(3, 4)))
void	ft_print_summary(t_buffer surv, t_plankb plan, t_blk8r name,
			t_u64a data[4])
{
	t_perf_sample	sum;
	t_u64a			total_iters;
	t_u64a			it;

	if (surv.mem == nullptr)
		__builtin_unreachable();
	ft_sum_counters((t_perf_sample *)surv.mem, &sum, surv.size);
	total_iters = plan.k_runs * plan.dp.iters;
	it = plan.dp.iters;
	ft_print_head(sum, plan, name, total_iters);
	ft_printf(" ├─ total_iters  = %lu\n"
		" ├─ med          = %luns [%lu, %lu] min=%luns\n"
		" ├─ relevant     = %lu samples (burst of=%lu iters)\n"
		" ├─ resamples    = %lu bootstrap_runs\n",
		total_iters,
		data[0] / it, data[2] / it, data[3] / it, data[1] / it,
		surv.size, plan.dp.iters, plan.b);
	ft_print_tail(sum);
}
