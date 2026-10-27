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

typedef void	(*t_tailor_fn)(t_any);

typedef struct s_tailor_bench
{
	t_tailor_fn		fn;
	t_blk8r			name;
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

typedef struct s_tailor
{
	t_arena				arena;
	t_perf_counters		counters;
	t_u64				phase1_ns;
	t_u64				phase2_ns;
	t_u64				min_samples;
	t_buffer			rand_buffers;
	t_arena_checkpoint	rpoint;
	t_u64a				swap;
	t_u8				buffer[TAILOR_BUFFER_SIZE];
	t_writer			writer;
}	t_tailor;

typedef struct s_tailor_report_ctx
{
	t_blk8r							name;
	t_writer *__restrict__ const	writer;
}	t_tailor_report_ctx;

#endif
