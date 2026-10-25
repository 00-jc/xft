/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_umap_str.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stl_bench_umap_str.hpp"

static void	std_umap_str_bench_insert(void *ptr, t_std_umap_str &map)
{
	const t_stl_str *const	keys = xft_get_bench_str_keys();
	uint64_t				n;
	uint64_t				i;
	uint64_t				bytes;

	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		i = n % STL_BENCH_KEYS;
		map.insert_or_assign(xft_stl_str_view(keys[i]),
			xft_stl_str_view(keys[i ^ 1]));
		bytes += keys[i].size;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_std_umap_str_bench_insert_grow(void *ptr)
{
	t_std_umap_str	map;

	std_umap_str_bench_insert(ptr, map);
}

void	xft_std_umap_str_bench_insert_reserved(void *ptr)
{
	t_std_umap_str	map;
	uint64_t		cap;

	cap = xft_tailor_getcount(ptr);
	if (cap > STL_BENCH_KEYS)
		cap = STL_BENCH_KEYS;
	map.reserve(cap);
	std_umap_str_bench_insert(ptr, map);
}

void	xft_std_umap_str_bench_lookup_hit(void *ptr)
{
	xft_std_umap_str_lookup(ptr, xft_get_bench_std_umap_str_filled(),
		xft_get_bench_str_keys(), STL_BENCH_FILL);
}

void	xft_std_umap_str_bench_lookup_miss(void *ptr)
{
	xft_std_umap_str_lookup(ptr, xft_get_bench_std_umap_str_filled(),
		xft_get_bench_str_keys() + STL_BENCH_FILL, STL_BENCH_FILL);
}
