/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_test_misaligned.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memcpy/memcpy_test.h"

void	test_memcpy_misaligned(void)
{
	char	src[256];
	char	a[256];
	char	b[256];
	int		i;

	i = 0;
	while (i < 255)
	{
		src[i] = 'A' + (i % 26);
		i++;
	}
	src[255] = '\0';
	ft_memcpy(a + 1, src + 3, 100);
	memcpy(b + 1, src + 3, 100);
	ft_pin_invariant(memcmp(a + 1, b + 1, 100) == 0);
}
