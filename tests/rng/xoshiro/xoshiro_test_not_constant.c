/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xoshiro_test_not_constant.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/rng/xoshiro/xoshiro_test.h"

void	test_xoshiro_not_constant(void)
{
	t_xoshiro	x;
	t_u64a		a;
	t_u64a		b;

	ft_xoshiro_init(x);
	a = ft_xoshiro256ss(x);
	b = ft_xoshiro256ss(x);
	ft_pin_invariant_msg(a != b,
		ft_fatptr((t_u8 *)"xoshiro not constant",
			sizeof("xoshiro not constant") - 1));
}
