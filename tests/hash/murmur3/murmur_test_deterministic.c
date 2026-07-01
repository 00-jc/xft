/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murmur_test_deterministic.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/hash/murmur3/murmur_test.h"

void	test_murmur_deterministic(void)
{
	t_u128a	h1;
	t_u128a	h2;

	h1 = ft_murmur3((t_u8 *)"hello", 5);
	h2 = ft_murmur3((t_u8 *)"hello", 5);
	ft_pin_invariant(h1 == h2);
	h1 = ft_murmur3((t_u8 *)"world", 5);
	h2 = ft_murmur3((t_u8 *)"world", 5);
	ft_pin_invariant(h1 == h2);
}
