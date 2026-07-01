/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_test_misaligned.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memset/memset_test.h"

void	test_memset_misaligned(void)
{
	char	a[4096];
	char	b[4096];
	int		off;

	off = 1;
	while (off < 64)
	{
		ft_memset(a + off, 'Z', 4096 - off);
		memset(b + off, 'Z', 4096 - off);
		ft_pin_invariant(memcmp(a + off, b + off, 4096 - off) == 0);
		off += 7;
	}
}
