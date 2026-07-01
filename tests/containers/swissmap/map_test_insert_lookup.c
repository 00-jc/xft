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

	m = ft_map_new(a);
	val = 42;
	ft_pin_invariant(ft_map_insert(a, &m,
			ft_fatptr((t_u8 *)"key1", 4), (t_u8 *)&val));
	got = ft_map_lookup(&m, ft_fatptr((t_u8 *)"key1", 4));
	ft_pin_invariant(got != nullptr);
	ft_pin_invariant(*(int *)got == 42);
	ft_pin_invariant(ft_map_lookup(&m,
			ft_fatptr((t_u8 *)"nope", 4)) == nullptr);
	ft_map_destroy(a, &m);
}
