/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murmur_test_seed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/hash/murmur3/murmur_test.h"

void	test_murmur_seed(void)
{
	t_u128a	h1;
	t_u128a	h2;

	h1 = ft_murmur3_with_seed((t_u8 *)"test", 0, 4);
	h2 = ft_murmur3_with_seed((t_u8 *)"test", 1, 4);
	ft_pin_invariant(h1 != h2);
	h1 = ft_murmur3_with_seed((t_u8 *)"test", 42, 4);
	h2 = ft_murmur3_with_seed((t_u8 *)"test", 42, 4);
	ft_pin_invariant(h1 == h2);
}
