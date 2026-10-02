/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/str/str_test.h"

void	test_str(t_test *t)
{
	t_gpa		gpa;
	t_allocator	a;

	gpa = xft_gpa();
	a = xft_gpa_allocator(&gpa);
	xft_test_print(t, "Testing t_str...\n");
	test_str_new(a);
	test_str_push_back(a);
	test_str_extend(a);
	test_str_remove(a);
	xft_gpa_destroy(&gpa);
	xft_test_print(t, "  t_str: OK\n");
}
