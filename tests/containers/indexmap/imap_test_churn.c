/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imap_test_churn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/indexmap/imap_test.h"

#define IMAP_TEST_LIVE	400
#define IMAP_TEST_CHURN	100000

static t_buffer	churn_key(t_u64a *keys, t_size i)
{
	return (xft_fatptr((t_u8 *)&keys[i % IMAP_TEST_LIVE], sizeof(t_u64a)));
}

static void	churn_check(t_indexmap *m, t_u64a *keys, t_xoshiro rng)
{
	t_size	i;

	xft_pin_invariant(m->count == IMAP_TEST_LIVE);
	i = IMAP_TEST_LIVE;
	while (i-- > 0)
		xft_pin_invariant(xft_indexmap_lookup(m, churn_key(keys, i)) == i);
	keys[0] = xft_xoshiro256ss(rng);
	xft_pin_invariant(xft_indexmap_lookup(m, churn_key(keys, 0))
		== INDEXMAP_NPOS);
}

void	test_imap_churn(t_allocator a)
{
	t_indexmap	m;
	t_xoshiro	rng;
	t_u64a		keys[IMAP_TEST_LIVE];
	t_size		i;

	xft_xoshiro_init(rng);
	m = xft_new_indexmap(a);
	i = 0;
	while (i < IMAP_TEST_CHURN)
	{
		if (i >= IMAP_TEST_LIVE)
			xft_pin_invariant(xft_indexmap_delete(&m, churn_key(keys, i))
				== i % IMAP_TEST_LIVE);
		keys[i % IMAP_TEST_LIVE] = xft_xoshiro256ss(rng);
		xft_pin_invariant(xft_indexmap_insert(a, &m, churn_key(keys, i),
				i % IMAP_TEST_LIVE));
		xft_pin_invariant((m.count + m.tombstones) * 20
			< m.soa.capacity_elements * 17 + 20);
		++i;
	}
	churn_check(&m, keys, rng);
	xft_indexmap_destroy(a, &m);
}
