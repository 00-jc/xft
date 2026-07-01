/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/bzero/bzero_test.h"

void	test_bzero_large(void)
{
	char	a[4096];
	char	b[4096];

	memset(a, 'A', 4096);
	memset(b, 'A', 4096);
	ft_bzero(a, 4096);
	memset(b, 0, 4096);
	ft_pin_invariant(memcmp(a, b, 4096) == 0);
	memset(a, 'B', 4096);
	ft_bzero(a + 13, 3000);
	ft_pin_invariant(a[12] == 'B');
	ft_pin_invariant(a[13] == 0);
	ft_pin_invariant(a[3012] == 0);
	ft_pin_invariant(a[3013] == 'B');
}

void	test_bzero(t_test *t)
{
	ft_test_print(t, "Testing ft_bzero...\n");
	test_bzero_large();
	ft_test_print(t, "  ft_bzero: OK\n");
}
