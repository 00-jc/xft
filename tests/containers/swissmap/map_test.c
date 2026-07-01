/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/swissmap/map_test.h"

void	test_map(t_test *t)
{
	t_gpa		gpa;
	t_allocator	a;

	gpa = ft_gpa();
	a = ft_gpa_allocator(&gpa);
	ft_test_print(t, "Testing t_map (swissmap)...\n");
	test_map_insert_lookup(a);
	test_map_delete(a);
	test_map_overwrite(a);
	test_map_many(a);
	ft_gpa_destroy(&gpa);
	ft_test_print(t, "  t_map: OK\n");
}
