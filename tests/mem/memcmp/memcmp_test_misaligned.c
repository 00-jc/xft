/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp_test_misaligned.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memcmp/memcmp_test.h"

void	test_memcmp_misaligned(void)
{
	char	buf[128];
	char	ref[128];

	memset(buf, 'A', 128);
	memset(ref, 'A', 128);
	ft_pin_invariant(ft_memcmp(buf + 1, ref + 1, 50)
		== memcmp(buf + 1, ref + 1, 50));
	ft_pin_invariant(ft_memcmp(buf + 3, ref + 7, 30)
		== memcmp(buf + 3, ref + 7, 30));
	buf[10] = 'B';
	ref[10] = 'C';
	ft_pin_invariant((ft_memcmp(buf + 1, ref + 1, 20) > 0)
		== (memcmp(buf + 1, ref + 1, 20) > 0));
}
