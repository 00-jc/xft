/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr_test_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memchr/memchr_test.h"

void	test_memchr_long(void)
{
	char	buf[256];
	int		i;

	i = 0;
	while (i < 255)
	{
		buf[i] = 'A' + (i % 26);
		i++;
	}
	buf[255] = '\0';
	ft_pin_invariant(ft_memchr(buf, 'A', 256) == memchr(buf, 'A', 256));
	ft_pin_invariant(ft_memchr(buf, 'Z', 256) == memchr(buf, 'Z', 256));
	ft_pin_invariant(ft_memchr(buf + 10, 'A', 100)
		== memchr(buf + 10, 'A', 100));
	ft_pin_invariant(ft_memchr(buf + 63, 'B', 50) == memchr(buf + 63, 'B', 50));
	ft_pin_invariant(ft_memchr(buf, '\0', 256) == memchr(buf, '\0', 256));
}
