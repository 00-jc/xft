/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxh3_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/hash/xxh3/xxh3_test.h"

void	test_xxh3(t_test *t)
{
	int				i;
	t_misal_buffer	buf;

	i = 0;
	while (i < 1024)
	{
		buf[i] = (t_u8)(i % 256);
		i++;
	}
	ft_test_print(t, "Testing ft_xxh3_64bits...\n");
	test_xxh3_basic();
	test_xxh3_edge();
	test_xxh3_seeds();
	test_xxh3_lengths(buf);
	ft_test_print(t, "    ft_xxh3_64bits: OK\n");
}
