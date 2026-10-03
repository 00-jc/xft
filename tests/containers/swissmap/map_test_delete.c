/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/swissmap/map_test.h"

void	test_map_delete(t_allocator a)
{
	t_map	m;
	int		val;

	m = xft_new_map(a);
	val = 10;
	xft_map_insert(a, &m, xft_fatptr((t_u8 *)"del", 3), (t_u8 *)&val);
	xft_pin_invariant(xft_map_lookup(&m,
			xft_fatptr((t_u8 *)"del", 3)) != nullptr);
	xft_map_delete(&m, xft_fatptr((t_u8 *)"del", 3));
	xft_pin_invariant(xft_map_lookup(&m,
			xft_fatptr((t_u8 *)"del", 3)) == nullptr);
	xft_map_destroy(a, &m);
}
