/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tailor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:32:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 09:55:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAILOR_H
# define TAILOR_H

# include "perf.h"
# include "alloc.h"
# include "rng.h"
# include "primitives.h"
# include "mem.h"

typedef void	(*t_tailor_fn)(void *);

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
}	t_tailor;

t_result	ft_tailor_new(t_tailor *t, t_f64 warmup_sec, t_u64a min_samples)\
					__attribute__((nonnull(1)));

t_result	ft_tailor_bench(t_tailor *t, t_tailor_bench benches[],\
				t_size size)\
				__attribute__((__nonnull__(1, 2)));

t_size		ft_tailor_getcount(const void *ptr)\
				__attribute__((pure, __nonnull__(1)));

t_result	ft_tailor_buffers(t_tailor *t, t_size *sizes,\
				t_u8 *alignment, t_size n)\
				__attribute__((__nonnull__(1, 2, 3)));

t_buffer	ft_get_random_buffer(const void *ptr)\
				__attribute__((__nonnull__(1)));

void		ft_tailor_destroy(t_tailor *t)\
				__attribute__((nonnull(1)));

t_buffer	*ft_get_all_buffers(const void *ptr, t_size *n)\
				__attribute__((__nonnull__(1)));

void		ft_tailor_add_processed_bytes(void *ptr, const t_size bytes)\
				__attribute__((__nonnull__(1)));

t_size		ft_tailor_get_random_num(void *ptr)\
				__attribute__((__nonnull__(1), __always_inline__));
#endif
