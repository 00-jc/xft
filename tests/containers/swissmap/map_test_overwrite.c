/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test_overwrite.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/swissmap/map_test.h"

void	test_map_overwrite(t_allocator a)
{
	t_map	m;
	int		v1;
	int		v2;
	int		*got;

	m = xft_map_new(a);
	v1 = 100;
	v2 = 200;
	xft_map_insert(a, &m, xft_fatptr((t_u8 *)"ow", 2), (t_u8 *)&v1);
	xft_map_insert(a, &m, xft_fatptr((t_u8 *)"ow", 2), (t_u8 *)&v2);
	got = xft_map_lookup(&m, xft_fatptr((t_u8 *)"ow", 2));
	xft_pin_invariant(got != nullptr);
	xft_pin_invariant(*got == 200);
	xft_map_destroy(a, &m);
}
