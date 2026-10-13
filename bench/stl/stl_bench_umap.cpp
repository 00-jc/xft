/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_umap.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stl_bench_umap.hpp"

static void	std_umap_bench_insert(void *ptr, t_std_umap &map)
{
	uint64_t *const	keys = xft_get_bench_swiss_keys();
	uint64_t		n;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
		map.insert_or_assign(keys[n % STL_BENCH_KEYS],
			reinterpret_cast<uint8_t *>(keys));
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(uint64_t));
}

void	xft_std_umap_bench_insert_grow(void *ptr)
{
	t_std_umap	map;

	std_umap_bench_insert(ptr, map);
}

void	xft_std_umap_bench_insert_reserved(void *ptr)
{
	t_std_umap	map;
	uint64_t	cap;

	cap = xft_tailor_getcount(ptr);
	if (cap > STL_BENCH_KEYS)
		cap = STL_BENCH_KEYS;
	map.reserve(cap);
	std_umap_bench_insert(ptr, map);
}

void	xft_std_umap_bench_lookup_hit(void *ptr)
{
	xft_std_umap_lookup(ptr, xft_get_bench_std_umap_filled(),
		xft_get_bench_swiss_keys(), 0, STL_BENCH_FILL);
}

void	xft_std_umap_bench_lookup_miss(void *ptr)
{
	xft_std_umap_lookup(ptr, xft_get_bench_std_umap_filled(),
		xft_get_bench_swiss_keys(), STL_BENCH_FILL, STL_BENCH_FILL);
}
