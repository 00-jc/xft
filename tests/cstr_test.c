/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_cstr_to_str(t_allocator a);

void	test_cstr_to_str(t_allocator a)
{
	t_str	s;

	s = ft_cstr_to_str(a, "hello");
	ft_pin_invariant(s.mem != nullptr);
	ft_pin_invariant(s.size == 5);
	ft_pin_invariant(ft_memcmp(s.mem, "hello", 6) == 0);
	ft_str_destroy(a, &s);
	s = ft_cstr_to_str(a, "");
	ft_pin_invariant(s.mem == nullptr);
	ft_pin_invariant(s.size == 0);
}

int	main(void)
{
	t_gpa		gpa;
	t_allocator	a;

	gpa = ft_gpa();
	a = ft_gpa_allocator(&gpa);
	ft_printf("Testing ft_cstr_to_str...\n");
	test_cstr_to_str(a);
	ft_gpa_destroy(&gpa);
	ft_printf("  ft_cstr_to_str: OK\n");
	return (0);
}
