/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_test_large.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memcpy/memcpy_test.h"

void	test_memcpy_large(void)
{
	char	a[4096];
	char	b[4096];
	int		i;

	i = 0;
	while (i < 4096)
	{
		a[i] = 'A' + (i % 26);
		i++;
	}
	ft_memcpy(b, a, 4096);
	ft_pin_invariant(memcmp(a, b, 4096) == 0);
	ft_memcpy(b + 1, a + 3, 2000);
	ft_pin_invariant(memcmp(b + 1, a + 3, 2000) == 0);
}
