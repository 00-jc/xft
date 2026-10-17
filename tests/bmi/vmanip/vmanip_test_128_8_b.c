/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_128_8_b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_128_VEC

static void	check_cmp_128_8(void)
{
	t_vu128	io;
	t_vu128	v;

	io = xft_viota128();
	v = xft_vsplat128(7);
	xft_pin_invariant(xft_veqmask128(v, 7) == vmanip_full(16));
	xft_pin_invariant(xft_veqmask128(v, 6) == 0);
	xft_pin_invariant(xft_veqmask128(io, 3) == vmanip_bit(3, 16));
	xft_pin_invariant(xft_vtestmask128(io, 1)
		== vmanip_odd(16));
	xft_pin_invariant(xft_vtestmask128(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask128(io, 1, 2) == vmanip_range(16));
}

static void	check_compress_128_8(void)
{
	t_vu128	io;
	t_vu128	c;
	t_size	i;

	io = xft_viota128();
	c = xft_vcompress128(io,
			(t_u16a)vmanip_odd(16));
	i = 0;
	while (i < 16)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, 16));
		i++;
	}
	c = xft_vcompress128(io, 0);
	xft_pin_invariant(xft_vmask128(xft_vsplat128(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_128_8(void)
{
	t_u8	a[64];
	t_vu128	l;
	t_size	i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u8)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load128(a,
			(t_u16a)vmanip_even(16));
	i = 0;
	while (i < 16)
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == a[i]);
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load128(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[16 - 1] == 0);
}

void	test_vmanip_128_8_b(void)
{
	check_cmp_128_8();
	check_compress_128_8();
	check_load_128_8();
}

#else

void	test_vmanip_128_8_b(void)
{
}

#endif
