/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_128_16_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_128_VEC

static void	check_cmp_128_16(void)
{
	t_vu16_128	io;
	t_vu16_128	v;

	io = xft_viota128_16();
	v = xft_vsplat128_16(7);
	xft_pin_invariant(xft_veqmask128_16(v, 7) == vmanip_full(8));
	xft_pin_invariant(xft_veqmask128_16(v, 6) == 0);
	xft_pin_invariant(xft_veqmask128_16(io, 3) == vmanip_bit(3, 8));
	xft_pin_invariant(xft_vtestmask128_16(io, 1)
		== vmanip_odd(8));
	xft_pin_invariant(xft_vtestmask128_16(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask128_16(io, 1, 2) == vmanip_range(8));
}

static void	check_compress_128_16(void)
{
	t_vu16_128	io;
	t_vu16_128	c;
	t_size		i;

	io = xft_viota128_16();
	c = xft_vcompress128_16(io,
			vmanip_odd(8));
	i = 0;
	while (i < 8)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, 8));
		i++;
	}
	c = xft_vcompress128_16(io, 0);
	xft_pin_invariant(xft_vmask128_16(xft_vsplat128_16(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_128_16(void)
{
	t_u16		a[64];
	t_vu16_128	l;
	t_size		i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u16)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load128_16(a,
			vmanip_even(8));
	i = 0;
	while (i < 8)
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == a[i]);
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load128_16(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[8 - 1] == 0);
}

void	test_vmanip_128_16_b(void)
{
	check_cmp_128_16();
	check_compress_128_16();
	check_load_128_16();
}

#else

void	test_vmanip_128_16_b(void)
{
}

#endif
