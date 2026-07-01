/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memmove/memmove_test.h"

void	test_memmove_backward(void)
{
	char	a[512];
	char	b[512];
	int		i;

	i = 0;
	while (i < 512)
	{
		a[i] = (char)(i & 0xFF);
		b[i] = (char)(i & 0xFF);
		i++;
	}
	ft_memmove(a + 10, a + 3, 200);
	memmove(b + 10, b + 3, 200);
	ft_pin_invariant(memcmp(a, b, 512) == 0);
}

void	test_memmove(t_test *t)
{
	ft_test_print(t, "Testing ft_memmove...\n");
	test_memmove_backward();
	ft_test_print(t, "  ft_memmove: OK\n");
}
