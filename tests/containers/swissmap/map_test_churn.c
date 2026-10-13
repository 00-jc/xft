/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   map_test_churn.c                                   :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/swissmap/map_test.h"

#define MAP_TEST_LIVE	400
#define MAP_TEST_CHURN	100000

static t_buffer	churn_key(t_u64a *keys, t_size i)
{
	return (xft_fatptr((t_u8 *)&keys[i % MAP_TEST_LIVE], sizeof(t_u64a)));
}

static void	churn_check(t_swissmap *m, t_u64a *keys, t_xoshiro rng)
{
	t_size	i;

	xft_pin_invariant(m->count == MAP_TEST_LIVE);
	i = MAP_TEST_LIVE;
	while (i-- > 0)
		xft_pin_invariant(xft_swissmap_lookup(m, churn_key(keys, i))
			!= nullptr);
	keys[0] = xft_xoshiro256ss(rng);
	xft_pin_invariant(xft_swissmap_lookup(m, churn_key(keys, 0)) == nullptr);
}

void	test_map_churn(t_allocator a)
{
	t_swissmap	m;
	t_xoshiro	rng;
	t_u64a		keys[MAP_TEST_LIVE];
	t_size		i;

	xft_xoshiro_init(rng);
	m = xft_new_swissmap(a);
	i = 0;
	while (i < MAP_TEST_CHURN)
	{
		if (i >= MAP_TEST_LIVE)
			xft_swissmap_delete(&m, churn_key(keys, i));
		keys[i % MAP_TEST_LIVE] = xft_xoshiro256ss(rng);
		xft_pin_invariant(xft_swissmap_insert(a, &m, churn_key(keys, i),
				(t_u8 *)keys));
		xft_pin_invariant((m.count + m.tombstones) * 20
			< m.soa.capacity_elements * 17 + 20);
		++i;
	}
	churn_check(&m, keys, rng);
	xft_swissmap_destroy(a, &m);
}
