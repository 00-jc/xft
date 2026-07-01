/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_test_basic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memset/memset_test.h"

void	test_memset_basic(void)
{
	char	a[64];
	char	b[64];

	ft_memset(a, 'X', 64);
	memset(b, 'X', 64);
	ft_pin_invariant(memcmp(a, b, 64) == 0);
	ft_memset(a, 0, 64);
	memset(b, 0, 64);
	ft_pin_invariant(memcmp(a, b, 64) == 0);
	ft_memset(a, 0xFF, 32);
	memset(b, 0xFF, 32);
	ft_pin_invariant(memcmp(a, b, 64) == 0);
}
