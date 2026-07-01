/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxh3_test_lengths_large.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/hash/xxh3/xxh3_test.h"

__attribute__((__nonnull__(1)))
void	test_xxh3_lengths_large(t_u8 *seq)
{
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq, .size = 256},
			0) == H_256B_S0, ft_fatptr((t_u8 *)"256B seq seed0",
			sizeof("256B seq seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq, .size = 256},
			42) == H_256B_S42, ft_fatptr((t_u8 *)"256B seq seed42",
			sizeof("256B seq seed42") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq,
			.size = 1024}, 0) == H_1024B_S0, ft_fatptr((t_u8 *)
			"1024B seq seed0", sizeof("1024B seq seed0") - 1));
	ft_pin_invariant_msg(ft_xxh3_64bits((t_buffer){.mem = seq,
			.size = 1024}, 42) == H_1024B_S42, ft_fatptr((t_u8 *)
			"1024B seq seed42", sizeof("1024B seq seed42") - 1));
}
