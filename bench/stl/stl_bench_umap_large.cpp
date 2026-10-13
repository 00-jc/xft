/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_umap_large.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stl_bench_umap.hpp"

void	xft_std_umap_bench_delete_insert(void *ptr)
{
	xft_std_umap_delete_insert(ptr, xft_get_bench_std_umap_filled(),
		xft_get_bench_swiss_keys(), STL_BENCH_FILL);
}

void	xft_std_umap_bench_large_lookup_hit(void *ptr)
{
	xft_std_umap_lookup(ptr, xft_get_bench_std_umap_large_filled(),
		xft_get_bench_swiss_large_keys(), 0, STL_BENCH_LARGE_FILL);
}

void	xft_std_umap_bench_large_lookup_miss(void *ptr)
{
	xft_std_umap_lookup(ptr, xft_get_bench_std_umap_large_filled(),
		xft_get_bench_swiss_large_keys(), STL_BENCH_LARGE_FILL,
		STL_BENCH_LARGE_FILL);
}

void	xft_std_umap_bench_large_delete_insert(void *ptr)
{
	xft_std_umap_delete_insert(ptr, xft_get_bench_std_umap_large_filled(),
		xft_get_bench_swiss_large_keys(), STL_BENCH_LARGE_FILL);
}
