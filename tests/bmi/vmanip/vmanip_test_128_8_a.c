/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_128_8_a.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_128_VEC

static void	check_splat_128_8(void)
{
	t_vu128	v;
	t_size	i;

	v = xft_vsplat128(5);
	i = 0;
	while (i < 16)
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_128_8(void)
{
	t_vu128	v;
	t_size	i;

	v = xft_viota128();
	i = 0;
	while (i < 16)
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_128_8(void)
{
	t_vu128	v;
	t_size	i;

	v = xft_vsplat128(0);
	i = 1;
	while (i < 16)
	{
		v[i] = (t_u8)1 << 7;
		i += 2;
	}
	xft_pin_invariant(xft_vmask128(v) == vmanip_odd(16));
	xft_pin_invariant(xft_vmask128(xft_vsplat128(1)) == 0);
}

void	test_vmanip_128_8_a(void)
{
	check_splat_128_8();
	check_iota_128_8();
	check_mask_128_8();
}

#else

void	test_vmanip_128_8_a(void)
{
}

#endif
