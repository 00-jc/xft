/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/str/str_test.h"

void	test_str_remove(t_allocator a)
{
	t_str		s;
	const t_u8	*src;

	src = (const t_u8 *)"abc";
	s = ft_str(a, 1);
	ft_pin_invariant(ft_str_extend(a, &s, src, 3));
	ft_pin_invariant(s.size == 3);
	ft_pin_invariant(ft_str_remove(&s, 1));
	ft_pin_invariant(s.size == 2);
	ft_pin_invariant(s.mem[0] == 'a');
	ft_pin_invariant(s.mem[1] == 'c');
	ft_pin_invariant(s.mem[2] == 0);
	ft_pin_invariant(!ft_str_remove(&s, 5));
	ft_pin_invariant(ft_str_remove(&s, 0));
	ft_pin_invariant(s.size == 1);
	ft_pin_invariant(s.mem[0] == 'c');
	ft_pin_invariant(s.mem[1] == 0);
	ft_pin_invariant(ft_str_remove(&s, 0));
	ft_pin_invariant(s.size == 0);
	ft_pin_invariant(s.mem[0] == 0);
	ft_str_destroy(a, &s);
}
