/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_256_8_b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_256_VEC

static void	check_cmp_256_8(void)
{
	t_vu256	io;
	t_vu256	v;

	io = xft_viota256();
	v = xft_vsplat256(7);
	xft_pin_invariant(xft_veqmask256(v, 7) == vmanip_full(32));
	xft_pin_invariant(xft_veqmask256(v, 6) == 0);
	xft_pin_invariant(xft_veqmask256(io, 3) == vmanip_bit(3, 32));
	xft_pin_invariant(xft_vtestmask256(io, 1)
		== vmanip_odd(32));
	xft_pin_invariant(xft_vtestmask256(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask256(io, 1, 2) == vmanip_range(32));
}

static void	check_compress_256_8(void)
{
	t_vu256	io;
	t_vu256	c;
	t_size	i;

	io = xft_viota256();
	c = xft_vcompress256(io,
			(t_u32a)vmanip_odd(32));
	i = 0;
	while (i < 32)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, 32));
		i++;
	}
	c = xft_vcompress256(io, 0);
	xft_pin_invariant(xft_vmask256(xft_vsplat256(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_256_8(void)
{
	t_u8	a[64];
	t_vu256	l;
	t_size	i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u8)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load256(a,
			(t_u32a)vmanip_even(32));
	i = 0;
	while (i < 32)
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == a[i]);
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load256(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[32 - 1] == 0);
}

void	test_vmanip_256_8_b(void)
{
	check_cmp_256_8();
	check_compress_256_8();
	check_load_256_8();
}

#else

void	test_vmanip_256_8_b(void)
{
}

#endif
