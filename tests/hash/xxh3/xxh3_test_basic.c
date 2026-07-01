/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxh3_test_basic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/hash/xxh3/xxh3_test.h"

void	test_xxh3_basic(void)
{
	t_al64_buffer	h;
	t_al4_buffer	w;
	t_al8_buffer	a;

	ft_memcpy(h, "hello", 6);
	ft_memcpy(w, "world", 6);
	ft_memcpy(a, "abc", 4);
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = h, .size = 5}, 0)
		== H_HELLO5_S0, ft_fatptr((t_u8 *)"hello len5 seed0",
			sizeof("hello len5 seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = w, .size = 5}, 0)
		== H_WORLD5_S0, ft_fatptr((t_u8 *)"world len5 seed0",
			sizeof("world len5 seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = a, .size = 3}, 0)
		== H_ABC3_S0, ft_fatptr((t_u8 *)"abc len3 seed0",
			sizeof("abc len3 seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = a, .size = 2}, 0)
		== H_AB2_S0, ft_fatptr((t_u8 *)"ab len2 seed0",
			sizeof("ab len2 seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = a, .size = 1}, 0)
		== H_A1_S0, ft_fatptr((t_u8 *)"a len1 seed0",
			sizeof("a len1 seed0") - 1));
}
