/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_256_32_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_256_VEC

static void	check_splat_256_32(void)
{
	t_vu32_256	v;
	t_size		i;

	v = xft_vsplat256_32(5);
	i = 0;
	while (i < 8)
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_256_32(void)
{
	t_vu32_256	v;
	t_size		i;

	v = xft_viota256_32();
	i = 0;
	while (i < 8)
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_256_32(void)
{
	t_vu32_256	v;
	t_size		i;

	v = xft_vsplat256_32(0);
	i = 1;
	while (i < 8)
	{
		v[i] = (t_u32)1 << 31;
		i += 2;
	}
	xft_pin_invariant(xft_vmask256_32(v) == vmanip_odd(8));
	xft_pin_invariant(xft_vmask256_32(xft_vsplat256_32(1)) == 0);
}

void	test_vmanip_256_32_a(void)
{
	check_splat_256_32();
	check_iota_256_32();
	check_mask_256_32();
}

#else

void	test_vmanip_256_32_a(void)
{
}

#endif
