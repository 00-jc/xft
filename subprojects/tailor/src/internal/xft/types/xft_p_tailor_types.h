/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_tailor_types.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_TAILOR_TYPES_H
# define XFT_P_TAILOR_TYPES_H

# include <xft/primitives.h>
# include <xft/types/tailor_types.h>
# include <xft/types/indexmap_types.h>

typedef struct s_datapoint
{
	t_size		n;
	t_size		iters;
	t_size		bytes_processed;
	t_f64		mu;
	t_f64		m2;
	t_f64		min;
	t_f64		max;
}	t_datapoint;

typedef struct s_phase1
{
	t_u64a	sum;
	t_u64a	n;
	t_u64a	iters;
	t_u64a	cap;
}	t_phase1;

typedef struct s_plankb
{
	t_size		b;
	t_u64a		k;
	t_size		k_runs;
	t_datapoint	dp;
}	t_plankb;

# ifndef TAILOR_MAX
#  define TAILOR_MAX 8388608
# endif

# define K_REL_CI 0.01

typedef enum e_tailor_warmup : t_u8
{
	K_WARMUP = 3,
}	t_tailor_warmup;

typedef enum e_tailor_col : t_u8
{
	TAILOR_NS,
	TAILOR_N,
	TAILOR_CACHE_LL,
	TAILOR_CACHE_MISS,
	TAILOR_CYCLES,
	TAILOR_INSTR,
	TAILOR_BRANCHES,
	TAILOR_BRANCH_MISS,
	TAILOR_ALIGNMENT_FAULTS,
	TAILOR_PAGE_FAULTS,
	TAILOR_COLS,
}	t_tailor_col;

typedef struct s_tailor_job
{
	const t_tailor		*t;
	t_tailor_fn			fn;
	t_arena				*arena;
	long				*counters;
	t_buffer			buffers;
	t_tailor_arg		arg;
	t_plankb			plan;
	t_soa				soa;
	t_u64a				swap;
	t_result			status;
	t_tailor_result		result;
}	t_tailor_job;

typedef struct s_tailor_unit
{
	t_tailor_job		**jobs;
	t_size				n;
	t_arena				arena;
	t_perf_counters		counters;
}	t_tailor_unit;

typedef struct s_tailor_units
{
	t_indexmap			map;
	t_tailor_unit		*units;
	t_thread_task		*tasks;
	t_tailor_job		**order;
	t_size				*uid;
	t_size				n;
}	t_tailor_units;

typedef struct s_tailor_groups
{
	t_indexmap	map;
	t_size		*next;
	t_size		*head;
	t_size		*tail;
	t_size		count;
}	t_tailor_groups;

#endif
