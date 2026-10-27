/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexmap_bench_lookup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "indexmap_bench.h"

__attribute__((__nonnull__(1)))
void	xft_imap_bench_lookup_hit(t_any ptr)
{
	t_indexmap *const	map = xft_get_bench_imap_filled();
	t_size				n;
	t_size				r;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		r = xft_indexmap_lookup(map, xft_imap_bench_key(
					xft_tailor_get_random_num(ptr) % IMAP_BENCH_FILL));
		__asm__("" : : "r"(r) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64));
}

__attribute__((__nonnull__(1)))
void	xft_imap_bench_lookup_miss(t_any ptr)
{
	t_indexmap *const	map = xft_get_bench_imap_filled();
	t_size				n;
	t_size				r;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		r = xft_indexmap_lookup(map, xft_imap_bench_key(IMAP_BENCH_FILL
					+ xft_tailor_get_random_num(ptr) % IMAP_BENCH_FILL));
		__asm__("" : : "r"(r) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64));
}

__attribute__((__nonnull__(1)))
void	xft_imap_bench_delete_insert(t_any ptr)
{
	const t_allocator	a = xft_gpa_allocator(xft_get_bench_imap_gpa());
	t_indexmap *const	map = xft_get_bench_imap_filled();
	t_size				n;
	t_size				i;

	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		i = xft_tailor_get_random_num(ptr) % IMAP_BENCH_FILL;
		xft_pin_invariant(xft_indexmap_insert(a, map, xft_imap_bench_key(i),
				xft_indexmap_delete(map, xft_imap_bench_key(i))));
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64));
}
