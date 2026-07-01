/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test_extend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/str/str_test.h"

void	test_str_extend(t_allocator a)
{
	t_str		s;
	const t_u8	*hello;

	hello = (const t_u8 *)"hello";
	s = ft_str(a, 1);
	ft_pin_invariant(ft_str_extend(a, &s, hello, 5));
	ft_pin_invariant(s.size == 5);
	ft_pin_invariant(ft_memcmp(s.mem, "hello", 6) == 0);
	ft_pin_invariant(ft_str_extend(a, &s, (const t_u8 *)" world", 6));
	ft_pin_invariant(s.size == 11);
	ft_pin_invariant(ft_memcmp(s.mem, "hello world", 11) == 0);
	ft_str_destroy(a, &s);
}
