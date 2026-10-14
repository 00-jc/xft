/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_512_32_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_512_VEC

static void	check_cmp_512_32(void)
{
	t_vu32_512	io;
	t_vu32_512	v;

	io = xft_viota512_32();
	v = xft_vsplat512_32(7);
	xft_pin_invariant(xft_veqmask512_32(v, 7) == vmanip_full(16));
	xft_pin_invariant(xft_veqmask512_32(v, 6) == 0);
	xft_pin_invariant(xft_veqmask512_32(io, 3) == vmanip_bit(3, 16));
	xft_pin_invariant(xft_vtestmask512_32(io, 1)
		== vmanip_odd(16));
	xft_pin_invariant(xft_vtestmask512_32(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask512_32(io, 1, 2) == vmanip_range(16));
}

static void	check_compress_512_32(void)
{
	t_vu32_512	io;
	t_vu32_512	c;
	t_size		i;

	io = xft_viota512_32();
	c = xft_vcompress512_32(io,
			vmanip_odd(16));
	i = 0;
	while (i < 16)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, 16));
		i++;
	}
	c = xft_vcompress512_32(io, 0);
	xft_pin_invariant(xft_vmask512_32(xft_vsplat512_32(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_512_32(void)
{
	t_u32		a[64];
	t_vu32_512	l;
	t_size		i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u32)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load512_32(a,
			vmanip_even(16));
	i = 0;
	while (i < 16)
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == a[i]);
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load512_32(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[16 - 1] == 0);
}

void	test_vmanip_512_32_b(void)
{
	check_cmp_512_32();
	check_compress_512_32();
	check_load_512_32();
}

#else

void	test_vmanip_512_32_b(void)
{
}

#endif
