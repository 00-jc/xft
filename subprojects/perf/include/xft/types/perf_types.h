/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perf_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERF_TYPES_H
# define PERF_TYPES_H

# include <xft/types/linux_types.h>
# include <xft/primitives.h>
# include <xft/mem.h>
# include <xft/timing.h>
# include <xft/hint.h>

# ifndef XFT_CPU_SETSIZE
#  define XFT_CPU_SETSIZE	1024
# endif

typedef struct s_perf_sample
{
	t_u64a			ns;
	t_u64a			n;
	t_u64a			cache_ll;
	t_u64a			cache_miss;
	t_u64a			cycles;
	t_u64a			instr;
	t_u64a			branches;
	t_u64a			branch_miss;
	t_u64a			alignment_faults;
	t_u64a			page_faults;
}	t_perf_sample;

typedef enum e_perf_counters_n : t_u8
{
	HW_COUNTERS_N = 6,
	SW_COUNTERS_N = 3,
}	t_perf_counters_n;

typedef enum e_hw_counters
{
	CYCLES = xft_perf_count_hw_cpu_cycles,
	INSTR = xft_perf_count_hw_instructions,
	CACHEHITLL = xft_perf_count_hw_cache_ll,
	CACHEMISS = xft_perf_count_hw_cache_misses,
	BRANCH = xft_perf_count_hw_branch_instructions,
	BRANCHMISS = xft_perf_count_hw_branch_misses,
}	t_hw_counters;

typedef enum e_sw_counters
{
	DUMMY = xft_perf_count_sw_dummy,
	ALIGNMENT = xft_perf_count_sw_alignment_faults,
	PAGEFAULT = xft_perf_count_sw_page_faults,
}	t_sw_counters;

typedef long	t_perf_counters[9];

#endif
