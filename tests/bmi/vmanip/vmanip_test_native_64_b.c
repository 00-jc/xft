/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_native_64_b.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

static void	check_cmp_native_64(void)
{
	t_nvec64	io;
	t_nvec64	v;

	io = xft_viota64();
	v = xft_vsplat64(7);
	xft_pin_invariant(xft_veqmask64(v, 7) == vmanip_full(vmanip_n(8)));
	xft_pin_invariant(xft_veqmask64(v, 6) == 0);
	xft_pin_invariant(xft_veqmask64(io, 3) == vmanip_bit(3, vmanip_n(8)));
	xft_pin_invariant(xft_vtestmask64(io, 1)
		== vmanip_odd(vmanip_n(8)));
	xft_pin_invariant(xft_vtestmask64(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask64(io, 1, 2) == vmanip_range(vmanip_n(8)));
}

static void	check_compress_native_64(void)
{
	t_nvec64	io;
	t_nvec64	c;
	t_size		i;

	io = xft_viota64();
	c = xft_vcompress64(io,
			(t_nmask64)vmanip_odd(vmanip_n(8)));
	i = 0;
	while (i < vmanip_n(8))
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, vmanip_n(8)));
		i++;
	}
	c = xft_vcompress64(io, 0);
	xft_pin_invariant(xft_vmask64(xft_vsplat64(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_native_64(void)
{
	t_u64		a[64];
	t_nvec64	l;
	t_size		i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u64)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load64(a,
			(t_nmask64)vmanip_even(vmanip_n(8)));
	i = 0;
	while (i < vmanip_n(8))
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == (t_u64)(i * 3 + 1));
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load64(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[vmanip_n(8) - 1] == 0);
}

void	test_vmanip_native_64_b(void)
{
	check_cmp_native_64();
	check_compress_native_64();
	check_load_native_64();
}
