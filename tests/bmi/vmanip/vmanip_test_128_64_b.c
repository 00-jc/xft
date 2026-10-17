/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_128_64_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_128_VEC

static void	check_cmp_128_64(void)
{
	t_vu64_128	io;
	t_vu64_128	v;

	io = xft_viota128_64();
	v = xft_vsplat128_64(7);
	xft_pin_invariant(xft_veqmask128_64(v, 7) == vmanip_full(2));
	xft_pin_invariant(xft_veqmask128_64(v, 6) == 0);
	xft_pin_invariant(xft_veqmask128_64(io, 3) == vmanip_bit(3, 2));
	xft_pin_invariant(xft_vtestmask128_64(io, 1)
		== vmanip_odd(2));
	xft_pin_invariant(xft_vtestmask128_64(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask128_64(io, 1, 2) == vmanip_range(2));
}

static void	check_compress_128_64(void)
{
	t_vu64_128	io;
	t_vu64_128	c;
	t_size		i;

	io = xft_viota128_64();
	c = xft_vcompress128_64(io,
			(t_u8)vmanip_odd(2));
	i = 0;
	while (i < 2)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, 2));
		i++;
	}
	c = xft_vcompress128_64(io, 0);
	xft_pin_invariant(xft_vmask128_64(xft_vsplat128_64(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_128_64(void)
{
	t_u64		a[64];
	t_vu64_128	l;
	t_size		i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u64)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load128_64(a,
			(t_u8)vmanip_even(2));
	i = 0;
	while (i < 2)
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == a[i]);
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load128_64(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[2 - 1] == 0);
}

void	test_vmanip_128_64_b(void)
{
	check_cmp_128_64();
	check_compress_128_64();
	check_load_128_64();
}

#else

void	test_vmanip_128_64_b(void)
{
}

#endif
