/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_512_32_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_512_VEC

static void	check_splat_512_32(void)
{
	t_vu32_512	v;
	t_size		i;

	v = xft_vsplat512_32(5);
	i = 0;
	while (i < 16)
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_512_32(void)
{
	t_vu32_512	v;
	t_size		i;

	v = xft_viota512_32();
	i = 0;
	while (i < 16)
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_512_32(void)
{
	t_vu32_512	v;
	t_size		i;

	v = xft_vsplat512_32(0);
	i = 1;
	while (i < 16)
	{
		v[i] = (t_u32)1 << 31;
		i += 2;
	}
	xft_pin_invariant(xft_vmask512_32(v) == vmanip_odd(16));
	xft_pin_invariant(xft_vmask512_32(xft_vsplat512_32(1)) == 0);
}

void	test_vmanip_512_32_a(void)
{
	check_splat_512_32();
	check_iota_512_32();
	check_mask_512_32();
}

#else

void	test_vmanip_512_32_a(void)
{
}

#endif
