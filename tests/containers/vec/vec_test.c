/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/vec/vec_test.h"

void	test_vec(t_test *t)
{
	t_gpa		gpa;
	t_allocator	a;

	gpa = ft_gpa();
	a = ft_gpa_allocator(&gpa);
	ft_test_print(t, "Testing t_vec...\n");
	test_vec_push_get(a);
	test_vec_pop(a);
	test_vec_extend(a);
	test_vec_clear_reuse(a);
	ft_gpa_destroy(&gpa);
	ft_test_print(t, "  t_vec: OK\n");
}
