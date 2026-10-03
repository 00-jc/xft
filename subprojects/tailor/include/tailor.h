/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tailor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:45 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAILOR_H
# define TAILOR_H

# ifdef __linux__

#  include "perf.h"
#  include "alloc.h"
#  include "rng.h"
#  include "primitives.h"
#  include "mem.h"

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

#  define TAILOR_BUFFER_SIZE 1024ULL

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

t_result	xft_tailor_new(t_tailor *t, t_f64 warmup_sec, t_u64a min_samples)\
					__attribute__((__nonnull__(1)));

t_result	xft_tailor_bench(t_tailor *t, t_tailor_bench benches[],\
				t_size size)\
				__attribute__((__nonnull__(1, 2)));

t_size		xft_tailor_getcount(t_cany ptr)\
				__attribute__((pure, __nonnull__(1)));

t_result	xft_tailor_buffers(t_tailor *t, t_size *sizes,\
				t_u8 *alignment, t_size n)\
				__attribute__((__nonnull__(1, 2, 3)));

t_buffer	xft_get_random_buffer(t_cany ptr)\
				__attribute__((__nonnull__(1)));

void		xft_tailor_destroy(t_tailor *t)\
				__attribute__((__nonnull__(1)));

t_buffer	*xft_get_all_buffers(t_cany ptr, t_size *n)\
				__attribute__((__nonnull__(1)));

void		xft_tailor_add_processed_bytes(t_any ptr, const t_size bytes)\
				__attribute__((__nonnull__(1)));

t_size		xft_tailor_get_random_num(t_any ptr)\
				__attribute__((__nonnull__(1)));

# else

#  error "tailor.h is linux only: it is built on perf_event_open"

# endif
#endif
