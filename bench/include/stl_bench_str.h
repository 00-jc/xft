/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_str.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_BENCH_STR_H
# define STL_BENCH_STR_H

# include "swissmap_bench.h"
# include "stl_bench_std.h"

/* keys are 12..40 base64url bytes: long enough that a hash has to read them */

typedef enum e_stl_str_len : t_u8
{
	STL_STR_MIN = 12,
	STL_STR_SPAN = 29,
	STL_STR_MAX = 40,
}	t_stl_str_len;

void		xft_bench_str_gen(t_stl_str *strs, t_u8 *pool, t_size n);
t_stl_str	*xft_get_bench_str_keys(void);
t_stl_str	*xft_get_bench_str_large_keys(void);
t_swissmap	*xft_get_bench_swiss_str_filled(void);
t_swissmap	*xft_get_bench_swiss_str_large_filled(void);
void		xft_swiss_str_lookup(t_any ptr, const t_swissmap *map,
				const t_stl_str *keys, t_size range);
void		xft_swiss_str_delete_insert(t_any ptr, t_swissmap *map,
				t_stl_str *keys, t_size range);

void		xft_swiss_str_bench_insert_grow(t_any ptr);
void		xft_swiss_str_bench_insert_reserved(t_any ptr);
void		xft_swiss_str_bench_lookup_hit(t_any ptr);
void		xft_swiss_str_bench_lookup_miss(t_any ptr);
void		xft_swiss_str_bench_delete_insert(t_any ptr);
void		xft_swiss_str_bench_large_lookup_hit(t_any ptr);
void		xft_swiss_str_bench_large_lookup_miss(t_any ptr);
void		xft_swiss_str_bench_large_delete_insert(t_any ptr);

/* the value of key i is key i ^ 1: another string, no second pool */
__attribute__((__always_inline__))
static inline t_buffer	xft_swiss_str_key(const t_stl_str *k)
{
	return (xft_fatptr(k->mem, k->size));
}

#endif
