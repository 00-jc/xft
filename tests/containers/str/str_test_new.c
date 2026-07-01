/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/str/str_test.h"

void	test_str_new(t_allocator a)
{
	t_str	s;

	s = ft_str(a, 1);
	ft_pin_invariant(s.mem != nullptr);
	ft_pin_invariant(s.size == 0);
	ft_pin_invariant(s.mem[0] == 0);
	ft_str_destroy(a, &s);
	ft_pin_invariant(s.mem == nullptr);
	ft_pin_invariant(s.size == 0);
	s = ft_str(a, 5);
	ft_pin_invariant(s.mem != nullptr);
	ft_pin_invariant(s.size == 0);
	ft_pin_invariant(s.mem[5] == 0);
	ft_str_destroy(a, &s);
}
