/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp_test_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memcmp/memcmp_test.h"

void	test_memcmp_long(void)
{
	char	a[256];
	char	b[256];
	char	c[256];
	int		i;

	i = 0;
	while (i < 256)
	{
		a[i] = (char)(i % 128);
		b[i] = a[i];
		c[i] = a[i];
		i++;
	}
	c[150] = 'X';
	ft_pin_invariant(ft_memcmp(a, b, 256) == 0);
	ft_pin_invariant((ft_memcmp(a, c, 256) != 0) == (memcmp(a, c, 256) != 0));
}
