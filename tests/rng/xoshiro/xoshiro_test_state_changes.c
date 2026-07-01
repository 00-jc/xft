/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xoshiro_test_state_changes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/rng/xoshiro/xoshiro_test.h"

void	test_xoshiro_state_changes(void)
{
	t_xoshiro	x;
	t_xoshiro	copy;
	int			i;
	int			same;

	ft_xoshiro_init(x);
	i = 0;
	while (i < 4)
	{
		copy[i] = x[i];
		i++;
	}
	ft_xoshiro256ss(x);
	same = 1;
	i = 0;
	while (i < 4)
	{
		if (x[i] != copy[i])
			same = 0;
		i++;
	}
	ft_pin_invariant_msg(same == 0,
		ft_fatptr((t_u8 *)"same != 0", sizeof("same != 0") - 1));
}
