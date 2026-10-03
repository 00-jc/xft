/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuzzer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUZZER_H
# define FUZZER_H

# include "alloc.h"
# include "rng.h"
# include "mem.h"

# define XFT_FUZZ_MIN_INIT 50000
# define XFT_FUZZ_MAX_INIT 300000

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

t_fuzzer	xft_new_fuzzer(t_arena arena);
t_result	xft_fuzzer_add_rand(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));

t_buffer	*xft_fuzz_get_rand(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));
t_u64a		xft_fuzz_get_rand_u(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));
t_f64		xft_fuzz_get_rand_d(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));

void		xft_fuzzer_destroy(t_fuzzer *f)\
				__attribute__((__nonnull__(1)));

#endif
