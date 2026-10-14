/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_512_8_b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_512_VEC

static void	check_cmp_512_8(void)
{
	t_vu512	io;
	t_vu512	v;

	io = xft_viota512();
	v = xft_vsplat512(7);
	xft_pin_invariant(xft_veqmask512(v, 7) == vmanip_full(64));
	xft_pin_invariant(xft_veqmask512(v, 6) == 0);
	xft_pin_invariant(xft_veqmask512(io, 3) == vmanip_bit(3, 64));
	xft_pin_invariant(xft_vtestmask512(io, 1)
		== vmanip_odd(64));
	xft_pin_invariant(xft_vtestmask512(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask512(io, 1, 2) == vmanip_range(64));
}

static void	check_compress_512_8(void)
{
	t_vu512	io;
	t_vu512	c;
	t_size	i;

	io = xft_viota512();
	c = xft_vcompress512(io,
			vmanip_odd(64));
	i = 0;
	while (i < 64)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, 64));
		i++;
	}
	c = xft_vcompress512(io, 0);
	xft_pin_invariant(xft_vmask512(xft_vsplat512(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_512_8(void)
{
	t_u8	a[64];
	t_vu512	l;
	t_size	i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u8)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load512(a,
			vmanip_even(64));
	i = 0;
	while (i < 64)
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == a[i]);
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load512(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[64 - 1] == 0);
}

void	test_vmanip_512_8_b(void)
{
	check_cmp_512_8();
	check_compress_512_8();
	check_load_512_8();
}

#else

void	test_vmanip_512_8_b(void)
{
}

#endif
