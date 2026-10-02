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

	xft_xoshiro_init(x);
	a = xft_xoshiro256ss(x);
	b = xft_xoshiro256ss(x);
	xft_pin_invariant_msg(a != b,
		xft_fatptr((t_u8 *)"xoshiro not constant",
			sizeof("xoshiro not constant") - 1));
}
