/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_test_basic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memcpy/memcpy_test.h"

void	test_memcpy_basic(void)
{
	char	src[20];
	char	a[20];
	char	b[20];

	memcpy(src, "hello world12345", 17);
	ft_memcpy(a, src, 17);
	memcpy(b, src, 17);
	ft_pin_invariant(memcmp(a, b, 17) == 0);
	ft_memcpy(a, src, 0);
	ft_pin_invariant(memcmp(a, b, 17) == 0);
	memcpy(src, "hello world1", 13);
	ft_memcpy(a, src, 13);
	memcpy(b, src, 13);
	ft_pin_invariant(memcmp(a, b, 13) == 0);
	ft_memcpy(a, src, 0);
	ft_pin_invariant(memcmp(a, b, 13) == 0);
	memcpy(src, "hello world1", 3);
	ft_memcpy(a, src, 3);
	memcpy(b, src, 3);
	ft_pin_invariant(memcmp(a, b, 3) == 0);
	ft_memcpy(a, src, 0);
	ft_pin_invariant(memcmp(a, b, 3) == 0);
}
