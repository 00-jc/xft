/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_summary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:06:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/primitives.h>
#include <xft/xft_p_tailor.h>
#include <xft/macros.h>
#include <xft/fmt.h>
#include <xft/math.h>
#include <xft/vec.h>

#define H0		" * %s\n"
#define H1		" ├─ time         = %f ns per_call\n"
#define H2		" ├─ ipc          = %f\n"
#define H3		" ├─ GB/sec       = %f\n"
#define H4		" ├─ cycles       = %f per_call\n"
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
static inline void	xft_init_args(const t_tailor_result *r, t_u64a *args)
{
	args[0] = (t_u64a)(t_uptr)r->name;
	args[1] = xft_strlen(r->name);
	args[2] = (t_dp){.f = r->ns}.i;
	args[3] = (t_dp){.f = r->ipc}.i;
	args[4] = (t_dp){.f = r->gb_per_sec}.i;
	args[5] = (t_dp){.f = r->cycles}.i;
	args[6] = (t_dp){.f = r->instr}.i;
	args[7] = r->total_iters;
	args[8] = r->med;
	args[9] = r->lo;
	args[10] = r->hi;
	args[11] = r->min;
	args[12] = r->relevant;
	args[13] = r->burst;
	args[14] = r->resamples;
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline void	xft_init_args2(const t_tailor_result *r, t_u64a *args)
{
	args[15] = (t_dp){.f = xft_dtern(r->branches > 0,
			(t_f64)r->branch_miss / (t_f64)r->branches * 100.0, 0.0)}.i;
	args[16] = r->branch_miss;
	args[17] = r->branches;
	args[18] = (t_dp){.f = xft_dtern(r->cache_ll > 0,
			(t_f64)r->cache_miss / (t_f64)r->cache_ll * 100.0, 0.0)}.i;
	args[19] = r->cache_miss;
	args[20] = r->cache_ll;
	args[21] = r->alignment_faults;
	args[22] = r->page_faults;
}

__attribute__((__nonnull__(1)))
void	xft_tailor_report(t_tailor *t)
{
	const t_size			size = sizeof(ANSI_BCYAN H0 ANSI_RESET H1 H2 H3
			H4 H5 B3 B4 B5 B6 H6 H7 H8 H6 H9 H8 B1 B2 "\n") - 1;
	const t_tailor_result	*r;
	t_size					i;
	t_u64a					args[23];

	i = 0;
	while (i < xft_vec_len(&t->results, sizeof(t_tailor_result)))
	{
		r = xft_vec_get(&t->results, i++, sizeof(t_tailor_result));
		(xft_init_args(r, args), xft_init_args2(r, args));
		xft_fmt_writer(&t->writer, xft_fatptr(
				(t_u8 *)ANSI_BCYAN H0 ANSI_RESET H1 H2 H3 H4 H5
				B3 B4 B5 B6 H6 H7 H8 H6 H9 H8 B1 B2 "\n", size), args);
	}
	xft_writer_flush(&t->writer);
}
