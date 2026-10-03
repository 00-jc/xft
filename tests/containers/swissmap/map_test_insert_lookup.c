/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test_insert_lookup.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/swissmap/map_test.h"

void	test_map_insert_lookup(t_allocator a)
{
	t_map	m;
	int		val;
	int		*got;

	m = xft_new_map(a);
	val = 42;
	xft_pin_invariant(xft_map_insert(a, &m,
			xft_fatptr((t_u8 *)"key1", 4), (t_u8 *)&val));
	got = xft_map_lookup(&m, xft_fatptr((t_u8 *)"key1", 4));
	xft_pin_invariant(got != nullptr);
	xft_pin_invariant(*got == 42);
	xft_pin_invariant(xft_map_lookup(&m,
			xft_fatptr((t_u8 *)"nope", 4)) == nullptr);
	xft_map_destroy(a, &m);
}
