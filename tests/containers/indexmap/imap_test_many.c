/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imap_test_many.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/indexmap/imap_test.h"

#define IMAP_TEST_MANY	2000

void	test_imap_many(t_allocator a)
{
	t_indexmap	m;
	t_xoshiro	rng;
	t_u64a		keys[IMAP_TEST_MANY];
	t_size		i;

	xft_xoshiro_init(rng);
	m = xft_new_indexmap(a);
	i = 0;
	while (i < IMAP_TEST_MANY)
	{
		keys[i] = xft_xoshiro256ss(rng);
		xft_pin_invariant(xft_indexmap_insert(a, &m,
				xft_fatptr((t_u8 *)&keys[i], sizeof(t_u64a)), i * 7));
		++i;
	}
	xft_pin_invariant(m.count == IMAP_TEST_MANY);
	xft_pin_invariant(m.soa.capacity_elements > INDEXMAP_INITIAL_SIZE);
	while (i-- > 0)
		xft_pin_invariant(xft_indexmap_lookup(&m,
				xft_fatptr((t_u8 *)&keys[i], sizeof(t_u64a))) == i * 7);
	xft_indexmap_destroy(a, &m);
}
