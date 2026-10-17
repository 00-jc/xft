/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_256_16_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_256_VEC

static void	check_cmp_256_16(void)
{
	t_vu16_256	io;
	t_vu16_256	v;

	io = xft_viota256_16();
	v = xft_vsplat256_16(7);
	xft_pin_invariant(xft_veqmask256_16(v, 7) == vmanip_full(16));
	xft_pin_invariant(xft_veqmask256_16(v, 6) == 0);
	xft_pin_invariant(xft_veqmask256_16(io, 3) == vmanip_bit(3, 16));
	xft_pin_invariant(xft_vtestmask256_16(io, 1)
		== vmanip_odd(16));
	xft_pin_invariant(xft_vtestmask256_16(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask256_16(io, 1, 2) == vmanip_range(16));
}

static void	check_compress_256_16(void)
{
	t_vu16_256	io;
	t_vu16_256	c;
	t_size		i;

	io = xft_viota256_16();
	c = xft_vcompress256_16(io,
			(t_u16a)vmanip_odd(16));
	i = 0;
	while (i < 16)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, 16));
		i++;
	}
	c = xft_vcompress256_16(io, 0);
	xft_pin_invariant(xft_vmask256_16(xft_vsplat256_16(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_256_16(void)
{
	t_u16		a[64];
	t_vu16_256	l;
	t_size		i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u16)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load256_16(a,
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
	l = xft_vmask_load256_16(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[16 - 1] == 0);
}

void	test_vmanip_256_16_b(void)
{
	check_cmp_256_16();
	check_compress_256_16();
	check_load_256_16();
}

#else

void	test_vmanip_256_16_b(void)
{
}

#endif
