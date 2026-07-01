/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp_test_basic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memcmp/memcmp_test.h"

void	test_memcmp_basic(void)
{
	char	a[6];
	char	b[6];
	char	c[6];
	char	d[6];

	memcpy(a, "hello", 6);
	memcpy(b, "hello", 6);
	memcpy(c, "hellp", 6);
	memcpy(d, "hellm", 6);
	ft_pin_invariant(ft_memcmp(a, b, 5) == memcmp(a, b, 5));
	ft_pin_invariant((ft_memcmp(a, c, 5) < 0) == (memcmp(a, c, 5) < 0));
	ft_pin_invariant((ft_memcmp(a, d, 5) > 0) == (memcmp(a, d, 5) > 0));
	ft_pin_invariant(ft_memcmp(a, b, 0) == memcmp(a, b, 0));
	ft_pin_invariant(ft_memcmp(a, c, 4) == memcmp(a, c, 4));
}
