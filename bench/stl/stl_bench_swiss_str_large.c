/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_swiss_str_large.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "stl_bench_str.h"

__attribute__((__nonnull__(1)))
void	xft_swiss_str_bench_delete_insert(t_any ptr)
{
	xft_swiss_str_delete_insert(ptr, xft_get_bench_swiss_str_filled(),
		xft_get_bench_str_keys(), STL_BENCH_FILL);
}

__attribute__((__nonnull__(1)))
void	xft_swiss_str_bench_large_lookup_hit(t_any ptr)
{
	xft_swiss_str_lookup(ptr, xft_get_bench_swiss_str_large_filled(),
		xft_get_bench_str_large_keys(), STL_BENCH_LARGE_FILL);
}

__attribute__((__nonnull__(1)))
void	xft_swiss_str_bench_large_lookup_miss(t_any ptr)
{
	xft_swiss_str_lookup(ptr, xft_get_bench_swiss_str_large_filled(),
		xft_get_bench_str_large_keys() + STL_BENCH_LARGE_FILL,
		STL_BENCH_LARGE_FILL);
}

__attribute__((__nonnull__(1)))
void	xft_swiss_str_bench_large_delete_insert(t_any ptr)
{
	xft_swiss_str_delete_insert(ptr, xft_get_bench_swiss_str_large_filled(),
		xft_get_bench_str_large_keys(), STL_BENCH_LARGE_FILL);
}
