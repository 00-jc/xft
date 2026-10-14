/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_512_64_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_512_VEC

static void	check_cmp_512_64(void)
{
	t_vu64_512	io;
	t_vu64_512	v;

	io = xft_viota512_64();
	v = xft_vsplat512_64(7);
	xft_pin_invariant(xft_veqmask512_64(v, 7) == vmanip_full(8));
	xft_pin_invariant(xft_veqmask512_64(v, 6) == 0);
	xft_pin_invariant(xft_veqmask512_64(io, 3) == vmanip_bit(3, 8));
	xft_pin_invariant(xft_vtestmask512_64(io, 1)
		== vmanip_odd(8));
	xft_pin_invariant(xft_vtestmask512_64(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask512_64(io, 1, 2) == vmanip_range(8));
}

static void	check_compress_512_64(void)
{
	t_vu64_512	io;
	t_vu64_512	c;
	t_size		i;

	io = xft_viota512_64();
	c = xft_vcompress512_64(io,
			vmanip_odd(8));
	i = 0;
	while (i < 8)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, 8));
		i++;
	}
	c = xft_vcompress512_64(io, 0);
	xft_pin_invariant(xft_vmask512_64(xft_vsplat512_64(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_512_64(void)
{
	t_u64		a[64];
	t_vu64_512	l;
	t_size		i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u64)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load512_64(a,
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
	l = xft_vmask_load512_64(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[8 - 1] == 0);
}

void	test_vmanip_512_64_b(void)
{
	check_cmp_512_64();
	check_compress_512_64();
	check_load_512_64();
}

#else

void	test_vmanip_512_64_b(void)
{
}

#endif
