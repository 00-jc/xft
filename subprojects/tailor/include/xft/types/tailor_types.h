/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tailor_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAILOR_TYPES_H
# define TAILOR_TYPES_H

# include <xft/perf.h>
# include <xft/alloc.h>
# include <xft/rng.h>
# include <xft/primitives.h>
# include <xft/threads.h>
# include <xft/types/io_types.h>
# include <xft/types/vec_types.h>

typedef void	(*t_tailor_fn)(t_any);

typedef struct s_tailor_bench
{
	t_tailor_fn		fn;
	const char		*name;
	const char		*group;
}	t_tailor_bench;

typedef struct s_tailor_arg
{
	t_size		iters;
	t_buffer	buffers;
	t_xoshiro	xoshiro;
	t_size		bytes_processed;
}	t_tailor_arg;

typedef enum e_tailor_buf : t_u16
{
	TAILOR_BUFFER_SIZE = 1024,
}	t_tailor_buf;

typedef struct s_tailor_result
{
	const char	*name;
	const char	*group;
	t_f64		ns;
	t_f64		ipc;
	t_f64		gb_per_sec;
	t_f64		cycles;
	t_f64		instr;
	t_u64a		total_iters;
	t_u64a		med;
	t_u64a		lo;
	t_u64a		hi;
	t_u64a		min;
	t_u64a		relevant;
	t_u64a		burst;
	t_u64a		resamples;
	t_u64a		branches;
	t_u64a		branch_miss;
	t_u64a		cache_ll;
	t_u64a		cache_miss;
	t_u64a		alignment_faults;
	t_u64a		page_faults;
}	t_tailor_result;

typedef struct s_tailor
{
	t_gpa				gpa;
	t_arena				arena;
	t_threadpool		pool;
	t_vec				jobs;
	t_vec				results;
	t_u64				phase1_ns;
	t_u64				phase2_ns;
	t_u64				min_samples;
	t_buffer			rand_buffers;
	t_u8				buffer[TAILOR_BUFFER_SIZE];
	t_writer			writer;
}	t_tailor;

#endif
