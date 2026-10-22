/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imap_test_seeded.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 13:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/22 13:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/indexmap/imap_test.h"

#define IMAP_TEST_SEEDED	2000

static void	imap_seeded_check(t_indexmap *m, t_u64a *keys)
{
	t_buffer	k;
	t_size		i;

	i = IMAP_TEST_SEEDED;
	while (i-- > 0)
	{
		k = xft_fatptr((t_u8 *)&keys[i], sizeof(t_u64a));
		xft_pin_invariant(xft_indexmap_lookup_seeded(m,
				(t_imap_key){.key = k, .seed = 1}) == i);
		xft_pin_invariant(xft_indexmap_lookup_seeded(m,
				(t_imap_key){.key = k, .seed = 2}) == i * 3);
		xft_pin_invariant(xft_indexmap_lookup(m, k) == INDEXMAP_NPOS);
	}
}

static void	imap_seeded_delete(t_indexmap *m, t_u64a *keys)
{
	t_buffer	k;
	t_size		i;

	i = IMAP_TEST_SEEDED;
	while (i-- > 0)
	{
		k = xft_fatptr((t_u8 *)&keys[i], sizeof(t_u64a));
		xft_pin_invariant(xft_indexmap_delete(m, k) == INDEXMAP_NPOS);
		xft_pin_invariant(xft_indexmap_delete_seeded(m,
				(t_imap_key){.key = k, .seed = 1}) == i);
		xft_pin_invariant(xft_indexmap_lookup_seeded(m,
				(t_imap_key){.key = k, .seed = 1}) == INDEXMAP_NPOS);
		xft_pin_invariant(xft_indexmap_lookup_seeded(m,
				(t_imap_key){.key = k, .seed = 2}) == i * 3);
	}
	xft_pin_invariant(m->count == IMAP_TEST_SEEDED);
}

void	test_imap_seeded(t_allocator a)
{
	t_indexmap	m;
	t_u64a		keys[IMAP_TEST_SEEDED];
	t_buffer	k;
	t_size		i;

	m = xft_new_indexmap(a);
	i = 0;
	while (i < IMAP_TEST_SEEDED)
	{
		keys[i] = i;
		k = xft_fatptr((t_u8 *)&keys[i], sizeof(t_u64a));
		xft_pin_invariant(xft_indexmap_insert_seeded(a, &m,
				(t_imap_key){.key = k, .seed = 1}, i));
		xft_pin_invariant(xft_indexmap_insert_seeded(a, &m,
				(t_imap_key){.key = k, .seed = 2}, i * 3));
		++i;
	}
	xft_pin_invariant(m.count == IMAP_TEST_SEEDED * 2);
	xft_pin_invariant(m.soa.capacity_elements > INDEXMAP_INITIAL_SIZE);
	imap_seeded_check(&m, keys);
	imap_seeded_delete(&m, keys);
	xft_indexmap_destroy(a, &m);
}
