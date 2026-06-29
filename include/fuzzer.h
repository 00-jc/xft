/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuzzer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:49:07 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUZZER_H
# define FUZZER_H

# include "alloc.h"
# include "rng.h"
# include "mem.h"

# define FT_FUZZ_MIN_INIT 50000
# define FT_FUZZ_MAX_INIT 300000

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

t_fuzzer	ft_fuzzer_new(t_arena arena);
t_result	ft_fuzzer_add_rand(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));

t_buffer	*ft_fuzz_get_rand(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));
t_u64a		ft_fuzz_get_rand_u(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));
t_f64		ft_fuzz_get_rand_d(t_fuzzer *fuzz)\
				__attribute__((__nonnull__(1)));

void		ft_fuzzer_destroy(t_fuzzer *f)\
				__attribute__((__nonnull__(1)));

#endif
