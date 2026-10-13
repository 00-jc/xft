/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   swissmap_bench.h                                   :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWISSMAP_BENCH_H
# define SWISSMAP_BENCH_H

# include "swissmap.h"
# include "alloc.h"
# include "rng.h"
# include "rt.h"

# define SWISS_BENCH_FILL	4096
# define SWISS_BENCH_KEYS	8192
# define SWISS_BENCH_LARGE_FILL	1048576

t_gpa		*xft_get_bench_swiss_gpa(void);
t_u64a		*xft_get_bench_swiss_keys(void);
t_buffer	xft_swiss_bench_key(t_size i);
t_swissmap	*xft_get_bench_swiss_filled(void);
t_u64a		*xft_get_bench_swiss_large_keys(void);
t_buffer	xft_swiss_bench_large_key(t_size i);
t_swissmap	*xft_get_bench_swiss_large_filled(void);

void		xft_swiss_bench_insert_grow(t_any ptr);
void		xft_swiss_bench_insert_reserved(t_any ptr);
void		xft_swiss_bench_lookup_hit(t_any ptr);
void		xft_swiss_bench_lookup_miss(t_any ptr);
void		xft_swiss_bench_delete_insert(t_any ptr);
void		xft_swiss_bench_large_lookup_hit(t_any ptr);
void		xft_swiss_bench_large_lookup_miss(t_any ptr);
void		xft_swiss_bench_large_delete_insert(t_any ptr);

#endif
