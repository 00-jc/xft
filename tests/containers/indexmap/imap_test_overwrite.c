/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imap_test_overwrite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/indexmap/imap_test.h"

void	test_imap_overwrite(t_allocator a)
{
	t_indexmap	m;

	m = xft_new_indexmap(a);
	xft_indexmap_insert(a, &m, xft_fatptr((t_u8 *)"ow", 2), 100);
	xft_indexmap_insert(a, &m, xft_fatptr((t_u8 *)"ow", 2), 200);
	xft_pin_invariant(xft_indexmap_lookup(&m,
			xft_fatptr((t_u8 *)"ow", 2)) == 200);
	xft_pin_invariant(m.count == 1);
	xft_indexmap_destroy(a, &m);
}
