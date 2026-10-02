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

void	test_map_many(t_allocator a)
{
	t_map		m;
	t_xoshiro	rng;
	int			vals[200];
	t_u64a		keys[200];
	int			i;

	xft_xoshiro_init(rng);
	m = xft_map_new(a);
	i = 0;
	while (i < 200)
	{
		vals[i] = i * 7;
		keys[i] = xft_xoshiro256ss(rng);
		xft_map_insert(a, &m,
			xft_fatptr((t_u8 *)&keys[i], sizeof(t_u64a)), (t_u8 *)&vals[i]);
		i++;
	}
	xft_pin_invariant(*(int *)xft_map_lookup(&m,
			xft_fatptr((t_u8 *)&keys[i - 1], sizeof(t_u64a))) == 199 * 7);
	xft_map_destroy(a, &m);
}
