/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_summary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:06:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"
#include "private/ft_p_tailor.h"
#include "macros.h"
#include "io.h"
#include "fmt.h"
#include "bmi.h"
#include "tailor.h"
#include "math.h"

#define H0		" * %s\n"
#define H1		" ├─ time         = %f ns per_call\n"
#define H2		" ├─ ipc          = %f\n"
#define H3		" ├─ GB/sec       = %f\n"
#define H4		" ├─ cycles       = %f\n"
#define H5		" ├─ instr        = %f per_call\n"

#define H6	" │\n"
#define H7		" ├─ branch miss  = %f%%\n"
#define H8	" │  └───────────── total_ratio=%q/%q\n"
#define H9		" ├─ LL     miss  = %f%%\n"
#define B1		" ├─ align faults = %q\n"
#define B2		" └─ page  faults = %q\n"

#define B3		" ├─ total_iters  = %q\n"
#define B4		" ├─ med          = %qns [%q, %q] min=%qns\n"
#define B5		" ├─ relevant     = %q samples (burst of=%q iters)\n"
#define B6		" ├─ resamples    = %q bootstrap_runs\n"

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

__attribute__((__nonnull__(3, 4), __always_inline__))
static inline void	ft_init_args(t_perf_sample sum, t_plankb plan, t_u64a *data,
	t_u64a *args)
{
	t_u64a	total_iters;
	t_u64a	it;

	total_iters = plan.k_runs * plan.dp.iters;
	it = plan.dp.iters;
	args[2] = (t_dp){.f = ft_dtern(total_iters != 0,
			(t_f64)sum.ns / (t_f64)total_iters, 0.0)}.i;
	args[3] = (t_dp){.f = ft_dtern(sum.cycles != 0,
			(t_f64)sum.instr / (t_f64)sum.cycles, 0.0)}.i;
	args[4] = (t_dp){.f = ft_dtern(sum.ns != 0,
			(t_f64)plan.dp.bytes_processed / (t_f64)sum.ns
			* 1e9, 0.0) * 1e-9}.i;
	args[5] = (t_dp){.f = (t_f64)sum.cycles / (t_f64)plan.dp.iters}.i;
	args[6] = (t_dp){.f = (t_f64)sum.instr / (t_f64)plan.dp.iters}.i;
	args[7] = total_iters;
	args[8] = data[0] / it;
	args[9] = data[2] / it;
	args[10] = data[3] / it;
	args[11] = data[1] / it;
}

__attribute__((__nonnull__(4), __always_inline__))
static inline void	ft_init_args2(t_perf_sample sum, t_buffer surv,
	t_plankb plan, t_u64a *args)
{
	if (surv.mem == nullptr)
		__builtin_unreachable();
	args[12] = surv.size;
	args[13] = plan.dp.iters;
	args[14] = plan.b;
	args[15] = (t_dp){.f = ft_dtern(sum.branches > 0,
			(t_f64)sum.branch_miss / (t_f64)sum.branches
			* 100.0, 0.0)}.i;
	args[16] = sum.branch_miss;
	args[17] = sum.branches;
	args[18] = (t_dp){.f = ft_dtern(sum.cache_ll > 0,
			(t_f64)sum.cache_miss / (t_f64)sum.cache_ll
			* 100.0, 0.0)}.i;
	args[19] = sum.cache_miss;
	args[20] = sum.cache_ll;
	args[21] = sum.alignment_faults;
	args[22] = sum.page_faults;
}

__attribute__((__nonnull__(4)))
void	ft_print_summary(t_buffer surv, t_plankb plan, t_tailor_report_ctx ctx,
			t_u64a data[4])
{
	const t_size	size = sizeof(ANSI_BCYAN H0 ANSI_RESET H1 H2 H3 H4 H5
			B3 B4 B5 B6 H6 H7 H8 H6 H9 H8 B1 B2 "\n") - 1;
	t_perf_sample	sum;
	t_u64a			args[28];

	if (surv.mem == nullptr || ctx.name == nullptr)
		__builtin_unreachable();
	ft_sum_counters((t_perf_sample *)surv.mem, &sum, surv.size);
	args[0] = (t_u64a)(uintptr_t)ctx.name;
	args[1] = (t_u64a)ft_strlen((const char *)ctx.name);
	ft_init_args(sum, plan, data, args);
	ft_init_args2(sum, surv, plan, args);
	ft_fmt_writer(ctx.writer, ft_fatptr(
			(t_u8 *)ANSI_BCYAN H0 ANSI_RESET H1 H2 H3 H4 H5
			B3 B4 B5 B6 H6 H7 H8 H6 H9 H8 B1 B2 "\n", size), args);
}
