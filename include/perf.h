/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:15:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/18 20:36:11 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERF_H
# define PERF_H

# include <linux/perf_event.h>
# include <linux/bpf_perf_event.h>
# include <sys/syscall.h>
# include <sched.h>
# include <unistd.h>
# include "types.h"
# include <linux/prctl.h>
# include <sys/prctl.h>
# include <sys/ioctl.h>
# include "mem.h"
# include "timing.h"
# include "hint.h"

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

int				ft_bind_process_to_cpu(t_u32 cpu);
int				ft_perf_create_counters(t_perf_counters c)\
					__attribute__((__nonnull__(1)));
void			ft_perf_counters_reset(t_perf_counters c)\
					__attribute__((__nonnull__(1)));
void			ft_perf_counters_start(t_perf_counters c)\
					__attribute__((__nonnull__(1)));
void			ft_perf_counters_stop(t_perf_counters c)\
					__attribute__((__nonnull__(1)));
void			ft_perf_start_sample(t_perf_counters c, t_perf_sample *s)\
					__attribute__((__nonnull__(1, 2)));
int				ft_perf_collect_sample(size_t n,\
					t_perf_counters c, t_perf_sample *s)\
					__attribute__((__nonnull__(2, 3)));
void			ft_perf_destroy_counters(t_perf_counters c)\
					__attribute__((__nonnull__(1)));

#endif
