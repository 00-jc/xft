/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_native_8_b.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

static void	check_cmp_native_8(void)
{
	t_nvec	io;
	t_nvec	v;

	io = xft_viota();
	v = xft_vsplat(7);
	xft_pin_invariant(xft_veqmask(v, 7) == vmanip_full(XFT_NVEC_SIZE));
	xft_pin_invariant(xft_veqmask(v, 6) == 0);
	xft_pin_invariant(xft_veqmask(io, 3) == vmanip_bit(3, XFT_NVEC_SIZE));
	xft_pin_invariant(xft_vtestmask(io, 1)
		== vmanip_odd(XFT_NVEC_SIZE));
	xft_pin_invariant(xft_vtestmask(v, 8) == 0);
	xft_pin_invariant(xft_vrangemask(io, 1, 2) == vmanip_range(XFT_NVEC_SIZE));
}

static void	check_compress_native_8(void)
{
	t_nvec	io;
	t_nvec	c;
	t_size	i;

	io = xft_viota();
	c = xft_vcompress(io,
			vmanip_odd(XFT_NVEC_SIZE) & (t_nmask)-1);
	i = 0;
	while (i < XFT_NVEC_SIZE)
	{
		xft_pin_invariant(c[i] == vmanip_lane(i, XFT_NVEC_SIZE));
		i++;
	}
	c = xft_vcompress(io, 0);
	xft_pin_invariant(xft_vmask(xft_vsplat(0)) == 0);
	xft_pin_invariant(c[0] == 0);
}

static void	check_load_native_8(void)
{
	t_u8	a[64];
	t_nvec	l;
	t_size	i;

	i = 0;
	while (i < 64)
	{
		a[i] = (t_u8)(i * 3 + 1);
		i++;
	}
	l = xft_vmask_load(a,
			vmanip_even(XFT_NVEC_SIZE) & (t_nmask)-1);
	i = 0;
	while (i < XFT_NVEC_SIZE)
	{
		if (i % 2 == 0)
			xft_pin_invariant(l[i] == a[i]);
		else
			xft_pin_invariant(l[i] == 0);
		i++;
	}
	l = xft_vmask_load(a, 0);
	xft_pin_invariant(l[0] == 0);
	xft_pin_invariant(l[XFT_NVEC_SIZE - 1] == 0);
}

void	test_vmanip_native_8_b(void)
{
	check_cmp_native_8();
	check_compress_native_8();
	check_load_native_8();
}
