/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   swissmap_bench_lookup.c                            :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "swissmap_bench.h"

__attribute__((__nonnull__(1)))
void	xft_swiss_bench_lookup_hit(t_any ptr)
{
	t_swissmap *const	map = xft_get_bench_swiss_filled();
	t_size				n;
	t_any				r;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		r = xft_swissmap_lookup(map, xft_swiss_bench_key(
					xft_tailor_get_random_num(ptr) % SWISS_BENCH_FILL));
		__asm__("" : : "r"(r) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64));
}

__attribute__((__nonnull__(1)))
void	xft_swiss_bench_lookup_miss(t_any ptr)
{
	t_swissmap *const	map = xft_get_bench_swiss_filled();
	t_size				n;
	t_any				r;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		r = xft_swissmap_lookup(map, xft_swiss_bench_key(SWISS_BENCH_FILL
					+ xft_tailor_get_random_num(ptr) % SWISS_BENCH_FILL));
		__asm__("" : : "r"(r) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64));
}

__attribute__((__nonnull__(1)))
void	xft_swiss_bench_delete_insert(t_any ptr)
{
	const t_allocator	a = xft_gpa_allocator(xft_get_bench_swiss_gpa());
	t_swissmap *const	map = xft_get_bench_swiss_filled();
	t_size				n;
	t_size				i;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		i = xft_tailor_get_random_num(ptr) % SWISS_BENCH_FILL;
		xft_swissmap_delete(map, xft_swiss_bench_key(i));
		xft_pin_invariant(xft_swissmap_insert(a, map,
				xft_swiss_bench_key(i), (t_u8 *)xft_get_bench_swiss_keys()));
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64));
}
