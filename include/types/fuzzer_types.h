/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuzzer_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUZZER_TYPES_H
# define FUZZER_TYPES_H

# include "primitives.h"
# include "types/rng_primitives.h"
# include "types/arena_alloc_primitives.h"

typedef enum e_lastgentype
{
	BUFFER,
	UNSIGNED,
	DOUBLE,
}	t_lastgentype;

typedef struct s_lastgenval
{
	t_u64a		u;
	t_f64		d;
	t_buffer	*b;
}	t_lastgenval;

typedef struct s_lastgen
{
	t_lastgentype	type;
	t_lastgenval	as;
}	t_lastgen;

typedef struct s_fuzzer
{
	t_xoshiro	xo;
	t_size		buf_n;
	t_arena		arena;
	t_buffer	*buffers;
	t_lastgen	lastgen;
}	t_fuzzer;

#endif
