/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perf_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/06 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERF_TYPES_H
# define PERF_TYPES_H

# include <linux/perf_event.h>
# include "primitives.h"

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

# define HW_COUNTERS_N 6
# define SW_COUNTERS_N 3

typedef enum e_hw_counters
{
	CYCLES = PERF_COUNT_HW_CPU_CYCLES,
	INSTR = PERF_COUNT_HW_INSTRUCTIONS,
	CACHEHITLL = PERF_COUNT_HW_CACHE_LL,
	CACHEMISS = PERF_COUNT_HW_CACHE_MISSES,
	BRANCH = PERF_COUNT_HW_BRANCH_INSTRUCTIONS,
	BRANCHMISS = PERF_COUNT_HW_BRANCH_MISSES,
}	t_hw_counters;

typedef enum e_sw_counters
{
	DUMMY = PERF_COUNT_SW_DUMMY,
	ALIGNMENT = PERF_COUNT_SW_ALIGNMENT_FAULTS,
	PAGEFAULT = PERF_COUNT_SW_PAGE_FAULTS,
}	t_sw_counters;

typedef long	t_perf_counters[9];

#endif
