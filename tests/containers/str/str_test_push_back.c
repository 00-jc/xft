/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test_push_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/str/str_test.h"

void	test_str_push_back(t_allocator a)
{
	t_str	s;

	s = ft_str(a, 1);
	ft_pin_invariant(ft_str_push_back(a, &s, 'h'));
	ft_pin_invariant(ft_str_push_back(a, &s, 'i'));
	ft_pin_invariant(s.size == 2);
	ft_pin_invariant(s.mem[0] == 'h');
	ft_pin_invariant(s.mem[1] == 'i');
	ft_pin_invariant(s.mem[2] == 0);
	ft_str_destroy(a, &s);
}
