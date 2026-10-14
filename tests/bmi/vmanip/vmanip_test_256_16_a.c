/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_256_16_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_256_VEC

static void	check_splat_256_16(void)
{
	t_vu16_256	v;
	t_size		i;

	v = xft_vsplat256_16(5);
	i = 0;
	while (i < 16)
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_256_16(void)
{
	t_vu16_256	v;
	t_size		i;

	v = xft_viota256_16();
	i = 0;
	while (i < 16)
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_256_16(void)
{
	t_vu16_256	v;
	t_size		i;

	v = xft_vsplat256_16(0);
	i = 1;
	while (i < 16)
	{
		v[i] = (t_u16)1 << 15;
		i += 2;
	}
	xft_pin_invariant(xft_vmask256_16(v) == vmanip_odd(16));
	xft_pin_invariant(xft_vmask256_16(xft_vsplat256_16(1)) == 0);
}

void	test_vmanip_256_16_a(void)
{
	check_splat_256_16();
	check_iota_256_16();
	check_mask_256_16();
}

#else

void	test_vmanip_256_16_a(void)
{
}

#endif
