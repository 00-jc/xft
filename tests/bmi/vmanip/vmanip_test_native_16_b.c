/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_native_16_b.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

static void	check_cmp_native_16(void)
{
	t_nvec16	io;
	t_nvec16	v;

	io = xft_viota16();
	v = xft_vsplat16(7);
	xft_pin_invariant(xft_veqmask16(v, 7) == vmanip_full(vmanip_n(2)));
	xft_pin_invariant(xft_veqmask16(v, 6) == 0);
	xft_pin_invariant(xft_veqmask16(io, 3) == vmanip_bit(3, vmanip_n(2)));
	xft_pin_invariant(xft_vtestmask16(io, 1)
		== vmanip_odd(vmanip_n(2)));
	xft_pin_invariant(xft_vtestmask16(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask16(io, 1, 2) == vmanip_range(vmanip_n(2)));
}

static void	check_compress_native_16(void)
{
	t_nvec16	io;
	t_nvec16	c;
	t_size		i;

	io = xft_viota16();
	c = xft_vcompress16(io,
			(t_nmask16)vmanip_odd(vmanip_n(2)));
	i = 0;
	while (i < vmanip_n(2))
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, vmanip_n(2)));
		i++;
	}
	c = xft_vcompress16(io, 0);
	xft_pin_invariant(xft_vmask16(xft_vsplat16(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_native_16(void)
{
	t_u16		a[64];
	t_nvec16	l;
	t_size		i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u16)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load16(a,
			(t_nmask16)vmanip_even(vmanip_n(2)));
	i = 0;
	while (i < vmanip_n(2))
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == a[i]);
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load16(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[vmanip_n(2) - 1] == 0);
}

void	test_vmanip_native_16_b(void)
{
	check_cmp_native_16();
	check_compress_native_16();
	check_load_native_16();
}
