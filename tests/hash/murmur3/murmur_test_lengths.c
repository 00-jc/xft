/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murmur_test_lengths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/hash/murmur3/murmur_test.h"

void	test_murmur_lengths(void)
{
	char	buf[512];
	t_u128a	prev;
	t_u128a	cur;
	int		i;

	memset(buf, 'A', 512);
	prev = ft_murmur3((t_u8 *)buf, 1);
	i = 2;
	while (i <= 512)
	{
		cur = ft_murmur3((t_u8 *)buf, i);
		ft_pin_invariant(cur != prev);
		prev = cur;
		i += (i < 32) + 1;
	}
}
