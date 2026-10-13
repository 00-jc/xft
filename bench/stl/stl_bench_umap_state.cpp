/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_umap_state.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stl_bench_umap.hpp"

static void	std_umap_fill(t_std_umap &map, uint64_t *keys, uint64_t n)
{
	uint64_t	i;

	map.reserve(n);
	i = 0;
	while (i < n)
		map.insert_or_assign(keys[i++], reinterpret_cast<uint8_t *>(keys));
}

t_std_umap	&xft_get_bench_std_umap_filled(void)
{
	static t_std_umap	map;

	if (map.empty())
		std_umap_fill(map, xft_get_bench_swiss_keys(), STL_BENCH_FILL);
	return (map);
}

t_std_umap	&xft_get_bench_std_umap_large_filled(void)
{
	static t_std_umap	map;

	if (map.empty())
		std_umap_fill(map, xft_get_bench_swiss_large_keys(),
			STL_BENCH_LARGE_FILL);
	return (map);
}

void	xft_std_umap_lookup(void *ptr, const t_std_umap &map,
	const uint64_t *keys, uint64_t base, uint64_t range)
{
	t_std_umap::const_iterator	it;
	uint64_t					n;
	uint8_t						*r;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		it = map.find(keys[base + xft_tailor_get_random_num(ptr) % range]);
		r = (it == map.end()) ? nullptr : it->second;
		__asm__("" : : "r"(r) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(uint64_t));
}

void	xft_std_umap_delete_insert(void *ptr, t_std_umap &map,
	uint64_t *keys, uint64_t range)
{
	uint64_t	n;
	uint64_t	i;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		i = xft_tailor_get_random_num(ptr) % range;
		map.erase(keys[i]);
		map.insert_or_assign(keys[i], reinterpret_cast<uint8_t *>(keys));
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(uint64_t));
}
