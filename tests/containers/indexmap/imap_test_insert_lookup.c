/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imap_test_insert_lookup.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/indexmap/imap_test.h"

void	test_imap_insert_lookup(t_allocator a)
{
	t_indexmap	m;

	m = xft_new_indexmap(a);
	xft_pin_invariant(xft_indexmap_insert(a, &m,
			xft_fatptr((t_u8 *)"key1", 4), 42));
	xft_pin_invariant(xft_indexmap_insert(a, &m,
			xft_fatptr((t_u8 *)"key0", 4), 0));
	xft_pin_invariant(xft_indexmap_lookup(&m,
			xft_fatptr((t_u8 *)"key1", 4)) == 42);
	xft_pin_invariant(xft_indexmap_lookup(&m,
			xft_fatptr((t_u8 *)"key0", 4)) == 0);
	xft_pin_invariant(xft_indexmap_lookup(&m,
			xft_fatptr((t_u8 *)"nope", 4)) == INDEXMAP_NPOS);
	xft_pin_invariant(m.count == 2);
	xft_indexmap_destroy(a, &m);
}
