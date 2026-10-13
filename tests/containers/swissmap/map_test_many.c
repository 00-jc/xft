/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test_many.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/swissmap/map_test.h"

#define MAP_TEST_MANY	2000

void	test_map_many(t_allocator a)
{
	t_swissmap	m;
	t_xoshiro	rng;
	int			vals[MAP_TEST_MANY];
	t_u64a		keys[MAP_TEST_MANY];
	int			i;

	xft_xoshiro_init(rng);
	m = xft_new_swissmap(a);
	i = -1;
	while (++i < MAP_TEST_MANY)
	{
		vals[i] = i * 7;
		keys[i] = xft_xoshiro256ss(rng);
		xft_pin_invariant(xft_swissmap_insert(a, &m,
				xft_fatptr((t_u8 *)&keys[i], sizeof(t_u64a)),
				(t_u8 *)&vals[i]));
	}
	xft_pin_invariant(m.count == MAP_TEST_MANY);
	xft_pin_invariant(m.soa.capacity_elements > SWISS_INITIAL_SIZE);
	while (i-- > 0)
		xft_pin_invariant(*(int *)xft_swissmap_lookup(&m,
				xft_fatptr((t_u8 *)&keys[i], sizeof(t_u64a))) == i * 7);
	xft_swissmap_destroy(a, &m);
}
