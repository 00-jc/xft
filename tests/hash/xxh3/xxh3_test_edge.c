/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxh3_test_edge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/hash/xxh3/xxh3_test.h"

void	test_xxh3_edge(void)
{
	t_al32_buffer	z;
	t_misal_buffer	nul;
	t_al4_buffer	abcd;

	z[0] = '\0';
	nul[0] = '\0';
	ft_memcpy(abcd, "abcd", 5);
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = z, .size = 0}, 0)
		== H_NULL0_S0, ft_fatptr((t_u8 *)"empty len0 seed0",
			sizeof("empty len0 seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = nul, .size = 1}, 0)
		== H_NUL1_S0, ft_fatptr((t_u8 *)"nulbyte len1 seed0",
			sizeof("nulbyte len1 seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = abcd, .size = 4},
			0) == H_ABCD4_S0, ft_fatptr((t_u8 *)"abcd len4 seed0",
			sizeof("abcd len4 seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = z, .size = 0}, 42)
		== H_NULL0_S42, ft_fatptr((t_u8 *)"empty len0 seed42",
			sizeof("empty len0 seed42") - 1));
}
