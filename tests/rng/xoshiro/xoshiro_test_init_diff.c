/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xoshiro_test_init_diff.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/rng/xoshiro/xoshiro_test.h"

void	test_xoshiro_init_diff(void)
{
	t_xoshiro	a;
	t_xoshiro	b;
	int			i;
	int			diff;

	ft_xoshiro_init(a);
	ft_xoshiro_init(b);
	diff = 0;
	i = 0;
	while (i < 4)
	{
		if (a[i] != b[i])
			diff = 1;
		i++;
	}
	ft_pin_invariant_msg(diff == 1,
		ft_fatptr((t_u8 *)"diff != 1", sizeof("diff != 1") - 1));
}
