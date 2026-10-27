/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   swissmap_bench_insert.c                            :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "swissmap_bench.h"

static void	swiss_bench_insert(t_any ptr, t_allocator a, t_swissmap *map)
{
	t_size	n;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
		xft_pin_invariant(xft_swissmap_insert(a, map,
				xft_swiss_bench_key(n % SWISS_BENCH_KEYS),
				(t_u8 *)xft_get_bench_swiss_keys()));
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64));
}

__attribute__((__nonnull__(1)))
void	xft_swiss_bench_insert_grow(t_any ptr)
{
	const t_allocator	a = xft_gpa_allocator(xft_get_bench_swiss_gpa());
	t_swissmap			map;

	map = xft_new_swissmap(a);
	xft_pin_invariant(map.soa.ptr != nullptr);
	swiss_bench_insert(ptr, a, &map);
	xft_swissmap_destroy(a, &map);
}

__attribute__((__nonnull__(1)))
void	xft_swiss_bench_insert_reserved(t_any ptr)
{
	const t_allocator	a = xft_gpa_allocator(xft_get_bench_swiss_gpa());
	t_swissmap			map;
	t_size				cap;

	cap = xft_tailor_getcount(ptr);
	if (cap > SWISS_BENCH_KEYS)
		cap = SWISS_BENCH_KEYS;
	cap = ((cap * 2) + XFT_NVEC_SIZE - 1) & ~(t_size)(XFT_NVEC_SIZE - 1);
	map = xft_new_swissmap_with(a, cap);
	xft_pin_invariant(map.soa.ptr != nullptr);
	swiss_bench_insert(ptr, a, &map);
	xft_swissmap_destroy(a, &map);
}
