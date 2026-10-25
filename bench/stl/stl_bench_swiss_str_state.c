/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_swiss_str_state.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "stl_bench_str.h"

static void	swiss_str_fill(t_swissmap *map, t_stl_str *keys, t_size n)
{
	const t_allocator	a = xft_gpa_allocator(xft_get_bench_swiss_gpa());
	t_size				i;

	*map = xft_new_swissmap_with(a, n * 2);
	xft_pin_invariant(map->soa.ptr != nullptr);
	i = 0;
	while (i < n)
	{
		xft_pin_invariant(xft_swissmap_insert(a, map,
				xft_swiss_str_key(&keys[i]), (t_u8 *)&keys[i ^ 1]));
		++i;
	}
}

t_swissmap	*xft_get_bench_swiss_str_filled(void)
{
	static t_swissmap	map = {0};

	if (map.soa.ptr == nullptr)
		swiss_str_fill(&map, xft_get_bench_str_keys(), STL_BENCH_FILL);
	return (&map);
}

t_swissmap	*xft_get_bench_swiss_str_large_filled(void)
{
	static t_swissmap	map = {0};

	if (map.soa.ptr == nullptr)
		swiss_str_fill(&map, xft_get_bench_str_large_keys(),
			STL_BENCH_LARGE_FILL);
	return (&map);
}

void	xft_swiss_str_lookup(t_any ptr, const t_swissmap *map,
	const t_stl_str *keys, t_size range)
{
	const t_stl_str	*k;
	t_size			n;
	t_size			bytes;
	t_any			r;

	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		k = &keys[xft_tailor_get_random_num(ptr) % range];
		r = xft_swissmap_lookup(map, xft_swiss_str_key(k));
		bytes += k->size;
		__asm__("" : : "r"(r) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_swiss_str_delete_insert(t_any ptr, t_swissmap *map,
	t_stl_str *keys, t_size range)
{
	const t_allocator	a = xft_gpa_allocator(xft_get_bench_swiss_gpa());
	t_size				n;
	t_size				i;
	t_size				bytes;

	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		i = xft_tailor_get_random_num(ptr) % range;
		xft_swissmap_delete(map, xft_swiss_str_key(&keys[i]));
		xft_pin_invariant(xft_swissmap_insert(a, map,
				xft_swiss_str_key(&keys[i]), (t_u8 *)&keys[i ^ 1]));
		bytes += keys[i].size;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}
