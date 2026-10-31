/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_native_32_b.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

static void	check_cmp_native_32(void)
{
	t_nvec32	io;
	t_nvec32	v;

	io = xft_viota32();
	v = xft_vsplat32(7);
	xft_pin_invariant(xft_veqmask32(v, 7) == vmanip_full(vmanip_n(4)));
	xft_pin_invariant(xft_veqmask32(v, 6) == 0);
	xft_pin_invariant(xft_veqmask32(io, 3) == vmanip_bit(3, vmanip_n(4)));
	xft_pin_invariant(xft_vtestmask32(io, 1)
		== vmanip_odd(vmanip_n(4)));
	xft_pin_invariant(xft_vtestmask32(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask32(io, 1, 2) == vmanip_range(vmanip_n(4)));
}

static void	check_compress_native_32(void)
{
	t_nvec32	io;
	t_nvec32	c;
	t_size		i;

	io = xft_viota32();
	c = xft_vcompress32(io,
			(t_nmask32)vmanip_odd(vmanip_n(4)));
	i = 0;
	while (i < vmanip_n(4))
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, vmanip_n(4)));
		i++;
	}
	c = xft_vcompress32(io, 0);
	xft_pin_invariant(xft_vmask32(xft_vsplat32(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_native_32(void)
{
	t_u32		a[64];
	t_nvec32	l;
	t_size		i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u32)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load32(a,
			(t_nmask32)vmanip_even(vmanip_n(4)));
	i = 0;
	while (i < vmanip_n(4))
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == (t_u32)(i * 3 + 1));
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load32(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[vmanip_n(4) - 1] == 0);
}

void	test_vmanip_native_32_b(void)
{
	check_cmp_native_32();
	check_compress_native_32();
	check_load_native_32();
}
