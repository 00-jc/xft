/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_native_8_a.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

static void	check_splat_native_8(void)
{
	t_nvec	v;
	t_size	i;

	v = xft_vsplat(5);
	i = 0;
	while (i < XFT_NVEC_SIZE)
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_native_8(void)
{
	t_nvec	v;
	t_size	i;

	v = xft_viota();
	i = 0;
	while (i < XFT_NVEC_SIZE)
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_native_8(void)
{
	t_nvec	v;
	t_size	i;

	v = xft_vsplat(0);
	i = 1;
	while (i < XFT_NVEC_SIZE)
	{
		v[i] = (t_u8)1 << 7;
		i += 2;
	}
	xft_pin_invariant(xft_vmask(v) == vmanip_odd(XFT_NVEC_SIZE));
	xft_pin_invariant(xft_vmask(xft_vsplat(1)) == 0);
}

void	test_vmanip_native_8_a(void)
{
	check_splat_native_8();
	check_iota_native_8();
	check_mask_native_8();
}
