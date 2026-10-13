/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imap_test_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/indexmap/imap_test.h"

void	test_imap_delete(t_allocator a)
{
	t_indexmap	m;

	m = xft_new_indexmap(a);
	xft_pin_invariant(xft_indexmap_delete(&m,
			xft_fatptr((t_u8 *)"del", 3)) == INDEXMAP_NPOS);
	xft_indexmap_insert(a, &m, xft_fatptr((t_u8 *)"del", 3), 10);
	xft_indexmap_insert(a, &m, xft_fatptr((t_u8 *)"keep", 4), 11);
	xft_pin_invariant(xft_indexmap_delete(&m,
			xft_fatptr((t_u8 *)"del", 3)) == 10);
	xft_pin_invariant(xft_indexmap_lookup(&m,
			xft_fatptr((t_u8 *)"del", 3)) == INDEXMAP_NPOS);
	xft_pin_invariant(xft_indexmap_delete(&m,
			xft_fatptr((t_u8 *)"del", 3)) == INDEXMAP_NPOS);
	xft_pin_invariant(xft_indexmap_lookup(&m,
			xft_fatptr((t_u8 *)"keep", 4)) == 11);
	xft_pin_invariant(m.count == 1);
	xft_indexmap_clear(&m);
	xft_pin_invariant(m.count == 0 && m.tombstones == 0);
	xft_pin_invariant(xft_indexmap_lookup(&m,
			xft_fatptr((t_u8 *)"keep", 4)) == INDEXMAP_NPOS);
	xft_indexmap_destroy(a, &m);
}
