/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuzzer_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUZZER_TYPES_H
# define FUZZER_TYPES_H

# include <xft/alloc.h>
# include <xft/rng.h>

typedef enum e_xft_fuzz_init : t_u32
{
	XFT_FUZZ_MIN_INIT = 50000,
	XFT_FUZZ_MAX_INIT = 300000,
}	t_xft_fuzz_init;

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
