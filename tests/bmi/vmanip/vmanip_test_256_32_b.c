/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_256_32_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_256_VEC

static void	check_cmp_256_32(void)
{
	t_vu32_256	io;
	t_vu32_256	v;

	io = xft_viota256_32();
	v = xft_vsplat256_32(7);
	xft_pin_invariant(xft_veqmask256_32(v, 7) == vmanip_full(8));
	xft_pin_invariant(xft_veqmask256_32(v, 6) == 0);
	xft_pin_invariant(xft_veqmask256_32(io, 3) == vmanip_bit(3, 8));
	xft_pin_invariant(xft_vtestmask256_32(io, 1)
		== vmanip_odd(8));
	xft_pin_invariant(xft_vtestmask256_32(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask256_32(io, 1, 2) == vmanip_range(8));
}

static void	check_compress_256_32(void)
{
	t_vu32_256	io;
	t_vu32_256	c;
	t_size		i;

	io = xft_viota256_32();
	c = xft_vcompress256_32(io,
			vmanip_odd(8));
	i = 0;
	while (i < 8)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, 8));
		i++;
	}
	c = xft_vcompress256_32(io, 0);
	xft_pin_invariant(xft_vmask256_32(xft_vsplat256_32(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_256_32(void)
{
	t_u32		a[64];
	t_vu32_256	l;
	t_size		i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u32)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load256_32(a,
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
	l = xft_vmask_load256_32(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[8 - 1] == 0);
}

void	test_vmanip_256_32_b(void)
{
	check_cmp_256_32();
	check_compress_256_32();
	check_load_256_32();
}

#else

void	test_vmanip_256_32_b(void)
{
}

#endif
