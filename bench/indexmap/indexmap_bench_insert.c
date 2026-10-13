/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexmap_bench_insert.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "indexmap_bench.h"

static void	imap_bench_insert(t_any ptr, t_allocator a, t_indexmap *map)
{
	t_size	n;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
		xft_pin_invariant(xft_indexmap_insert(a, map,
				xft_imap_bench_key(n % IMAP_BENCH_KEYS),
				n));
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64));
}

__attribute__((__nonnull__(1)))
void	xft_imap_bench_insert_grow(t_any ptr)
{
	const t_allocator	a = xft_gpa_allocator(xft_get_bench_imap_gpa());
	t_indexmap			map;

	map = xft_new_indexmap(a);
	xft_pin_invariant(map.soa.ptr != nullptr);
	imap_bench_insert(ptr, a, &map);
	xft_indexmap_destroy(a, &map);
}

__attribute__((__nonnull__(1)))
void	xft_imap_bench_insert_reserved(t_any ptr)
{
	const t_allocator	a = xft_gpa_allocator(xft_get_bench_imap_gpa());
	t_indexmap			map;
	t_size				cap;

	cap = xft_tailor_getcount(ptr);
	if (cap > IMAP_BENCH_KEYS)
		cap = IMAP_BENCH_KEYS;
	cap = ((cap * 2) + 15) & ~(t_size)15;
	map = xft_new_indexmap_with(a, cap);
	xft_pin_invariant(map.soa.ptr != nullptr);
	imap_bench_insert(ptr, a, &map);
	xft_indexmap_destroy(a, &map);
}
