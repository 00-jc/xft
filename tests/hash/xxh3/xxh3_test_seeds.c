/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxh3_test_seeds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/hash/xxh3/xxh3_test.h"

void	test_xxh3_seeds(void)
{
	t_al32_buffer	h;
	t_misal_buffer	a;

	ft_memcpy(h, "hello", 6);
	a[0] = 'a';
	a[1] = '\0';
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = h, .size = 5}, 0)
		== H_HELLO5_S0, ft_fatptr((t_u8 *)"hello seed0",
			sizeof("hello seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = h, .size = 5}, 1)
		== H_HELLO5_S1, ft_fatptr((t_u8 *)"hello seed1",
			sizeof("hello seed1") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = h, .size = 5}, 42)
		== H_HELLO5_S42, ft_fatptr((t_u8 *)"hello seed42",
			sizeof("hello seed42") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = h, .size = 5},
			(t_u64) - 1) == H_HELLO5_SFF, ft_fatptr((t_u8 *)"hello seedFF",
			sizeof("hello seedFF") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = a, .size = 1}, 42)
		== H_A1_S42, ft_fatptr((t_u8 *)"a seed42",
			sizeof("a seed42") - 1));
}
