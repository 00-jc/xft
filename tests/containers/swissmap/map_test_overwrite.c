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

	m = ft_map_new(a);
	v1 = 100;
	v2 = 200;
	ft_map_insert(a, &m, ft_fatptr((t_u8 *)"ow", 2), (t_u8 *)&v1);
	ft_map_insert(a, &m, ft_fatptr((t_u8 *)"ow", 2), (t_u8 *)&v2);
	got = ft_map_lookup(&m, ft_fatptr((t_u8 *)"ow", 2));
	ft_pin_invariant(got != nullptr);
	ft_pin_invariant(*(int *)got == 200);
	ft_map_destroy(a, &m);
}
