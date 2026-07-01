/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_test_large.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memset/memset_test.h"

void	test_memset_large(void)
{
	char	a[4096];
	char	b[4096];
	int		i;

	i = 0;
	while (i < 256)
	{
		ft_memset(a, (t_u8)i, 4096);
		memset(b, i, 4096);
		ft_pin_invariant(memcmp(a, b, 4096) == 0);
		i += 85;
	}
}
