/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/02 22:59:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/swissmap/map_test.h"

void	test_map(t_test *t)
{
	t_gpa		gpa;
	t_allocator	a;

	gpa = xft_new_gpa();
	a = xft_gpa_allocator(&gpa);
	xft_test_print(t, "Testing t_map (swissmap)...\n");
	test_map_insert_lookup(a);
	test_map_delete(a);
	test_map_overwrite(a);
	test_map_many(a);
	xft_gpa_destroy(&gpa);
	xft_test_print(t, "  t_map: OK\n");
}
