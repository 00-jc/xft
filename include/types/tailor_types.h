/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tailor_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAILOR_TYPES_H
# define TAILOR_TYPES_H

# include "primitives.h"
# include "types/arena_alloc_primitives.h"
# include "types/perf_primitives.h"
# include "types/rng_primitives.h"
# include "types/ft_p_asm_primitives.h"

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

#endif
