/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_swiss_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "stl_bench_str.h"

static void	swiss_str_bench_insert(t_any ptr, t_allocator a, t_swissmap *map)
{
	t_stl_str *const	keys = xft_get_bench_str_keys();
	t_size				n;
	t_size				i;
	t_size				bytes;

	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		i = n % STL_BENCH_KEYS;
		xft_pin_invariant(xft_swissmap_insert(a, map,
				xft_swiss_str_key(&keys[i]), (t_u8 *)&keys[i ^ 1]));
		bytes += keys[i].size;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

__attribute__((__nonnull__(1)))
void	xft_swiss_str_bench_insert_grow(t_any ptr)
{
	const t_allocator	a = xft_gpa_allocator(xft_get_bench_swiss_gpa());
	t_swissmap			map;

	map = xft_new_swissmap(a);
	xft_pin_invariant(map.soa.ptr != nullptr);
	swiss_str_bench_insert(ptr, a, &map);
	xft_swissmap_destroy(a, &map);
}

__attribute__((__nonnull__(1)))
void	xft_swiss_str_bench_insert_reserved(t_any ptr)
{
	const t_allocator	a = xft_gpa_allocator(xft_get_bench_swiss_gpa());
	t_swissmap			map;
	t_size				cap;

	cap = xft_tailor_getcount(ptr);
	if (cap > STL_BENCH_KEYS)
		cap = STL_BENCH_KEYS;
	cap = ((cap * 2) + XFT_NVEC_SIZE - 1) & ~(t_size)(XFT_NVEC_SIZE - 1);
	map = xft_new_swissmap_with(a, cap);
	xft_pin_invariant(map.soa.ptr != nullptr);
	swiss_str_bench_insert(ptr, a, &map);
	xft_swissmap_destroy(a, &map);
}

__attribute__((__nonnull__(1)))
void	xft_swiss_str_bench_lookup_hit(t_any ptr)
{
	xft_swiss_str_lookup(ptr, xft_get_bench_swiss_str_filled(),
		xft_get_bench_str_keys(), STL_BENCH_FILL);
}

__attribute__((__nonnull__(1)))
void	xft_swiss_str_bench_lookup_miss(t_any ptr)
{
	xft_swiss_str_lookup(ptr, xft_get_bench_swiss_str_filled(),
		xft_get_bench_str_keys() + STL_BENCH_FILL, STL_BENCH_FILL);
}
