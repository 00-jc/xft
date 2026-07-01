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

	m = ft_map_new(a);
	val = 10;
	ft_map_insert(a, &m, ft_fatptr((t_u8 *)"del", 3), (t_u8 *)&val);
	ft_pin_invariant(ft_map_lookup(&m, ft_fatptr((t_u8 *)"del", 3)) != nullptr);
	ft_map_delete(&m, ft_fatptr((t_u8 *)"del", 3));
	ft_pin_invariant(ft_map_lookup(&m, ft_fatptr((t_u8 *)"del", 3)) == nullptr);
	ft_map_destroy(a, &m);
}
