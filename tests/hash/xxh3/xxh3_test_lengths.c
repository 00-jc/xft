/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxh3_test_lengths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/hash/xxh3/xxh3_test.h"

__attribute__((__nonnull__(1)))
void	test_xxh3_lengths(t_u8 *seq)
{
	t_al64_buffer	buf;
	t_u8			*x;

	x = &buf[3];
	ft_memcpy(x, "abcdefghijklmnopq", 17);
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = x, .size = 8}, 0)
		== H_8B_S0, ft_fatptr((t_u8 *)"abcdefgh len8 seed0",
			sizeof("abcdefgh len8 seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = x, .size = 16},
			0) == H_16B_S0, ft_fatptr((t_u8 *)"16B seed0",
			sizeof("16B seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = x, .size = 17},
			0) == H_17B_S0, ft_fatptr((t_u8 *)"17B seed0",
			sizeof("17B seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq, .size = 128},
			0) == H_128B_S0, ft_fatptr((t_u8 *)"128B seq seed0",
			sizeof("128B seq seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq, .size = 240},
			0) == H_240B_S0, ft_fatptr((t_u8 *)"240B seq seed0",
			sizeof("240B seq seed0") - 1));
	test_xxh3_lengths_large(seq);
}
