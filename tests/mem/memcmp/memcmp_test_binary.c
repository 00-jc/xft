/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp_test_binary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memcmp/memcmp_test.h"

void	test_memcmp_binary(void)
{
	unsigned char	a[5];
	unsigned char	b[5];
	unsigned char	c[5];
	unsigned char	d[5];

	a[0] = 0x00;
	a[1] = 0xFF;
	a[2] = 0x80;
	a[3] = 0x01;
	a[4] = 0x7F;
	memcpy(b, a, 5);
	memcpy(c, a, 5);
	memcpy(d, a, 5);
	c[2] = 0x81;
	d[1] = 0xFE;
	ft_pin_invariant(ft_memcmp(a, b, 5) == 0);
	ft_pin_invariant((ft_memcmp(a, c, 5) < 0) == (memcmp(a, c, 5) < 0));
	ft_pin_invariant((ft_memcmp(a, d, 5) > 0) == (memcmp(a, d, 5) > 0));
}
