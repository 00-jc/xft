/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_256_64_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_256_VEC

static void	check_cmp_256_64(void)
{
	t_vu64_256	io;
	t_vu64_256	v;

	io = xft_viota256_64();
	v = xft_vsplat256_64(7);
	xft_pin_invariant(xft_veqmask256_64(v, 7) == vmanip_full(4));
	xft_pin_invariant(xft_veqmask256_64(v, 6) == 0);
	xft_pin_invariant(xft_veqmask256_64(io, 3) == vmanip_bit(3, 4));
	xft_pin_invariant(xft_vtestmask256_64(io, 1)
		== vmanip_odd(4));
	xft_pin_invariant(xft_vtestmask256_64(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask256_64(io, 1, 2) == vmanip_range(4));
}

static void	check_compress_256_64(void)
{
	t_vu64_256	io;
	t_vu64_256	c;
	t_size		i;

	io = xft_viota256_64();
	c = xft_vcompress256_64(io,
			(t_u8)vmanip_odd(4));
	i = 0;
	while (i < 4)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, 4));
		i++;
	}
	c = xft_vcompress256_64(io, 0);
	xft_pin_invariant(xft_vmask256_64(xft_vsplat256_64(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_256_64(void)
{
	t_u64		a[64];
	t_vu64_256	l;
	t_size		i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u64)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load256_64(a,
			(t_u8)vmanip_even(4));
	i = 0;
	while (i < 4)
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == a[i]);
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load256_64(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[4 - 1] == 0);
}

void	test_vmanip_256_64_b(void)
{
	check_cmp_256_64();
	check_compress_256_64();
	check_load_256_64();
}

#else

void	test_vmanip_256_64_b(void)
{
}

#endif
