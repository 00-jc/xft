/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_umap_str_state.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stl_bench_umap_str.hpp"

static void	std_umap_str_fill(t_std_umap_str &map, const t_stl_str *keys,
	uint64_t n)
{
	uint64_t	i;

	map.reserve(n);
	i = 0;
	while (i < n)
	{
		map.insert_or_assign(xft_stl_str_view(keys[i]),
			xft_stl_str_view(keys[i ^ 1]));
		++i;
	}
}

t_std_umap_str	&xft_get_bench_std_umap_str_filled(void)
{
	static t_std_umap_str	map;

	if (map.empty())
		std_umap_str_fill(map, xft_get_bench_str_keys(), STL_BENCH_FILL);
	return (map);
}

t_std_umap_str	&xft_get_bench_std_umap_str_large_filled(void)
{
	static t_std_umap_str	map;

	if (map.empty())
		std_umap_str_fill(map, xft_get_bench_str_large_keys(),
			STL_BENCH_LARGE_FILL);
	return (map);
}

void	xft_std_umap_str_lookup(void *ptr, const t_std_umap_str &map,
	const t_stl_str *keys, uint64_t range)
{
	t_std_umap_str::const_iterator	it;
	const t_stl_str					*k;
	uint64_t						n;
	uint64_t						bytes;
	const char						*r;

	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		k = &keys[xft_tailor_get_random_num(ptr) % range];
		it = map.find(xft_stl_str_view(*k));
		r = (it == map.end()) ? nullptr : it->second.data();
		bytes += k->size;
		__asm__("" : : "r"(r) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_std_umap_str_delete_insert(void *ptr, t_std_umap_str &map,
	const t_stl_str *keys, uint64_t range)
{
	uint64_t	n;
	uint64_t	i;
	uint64_t	bytes;

	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		i = xft_tailor_get_random_num(ptr) % range;
		map.erase(xft_stl_str_view(keys[i]));
		map.insert_or_assign(xft_stl_str_view(keys[i]),
			xft_stl_str_view(keys[i ^ 1]));
		bytes += keys[i].size;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}
