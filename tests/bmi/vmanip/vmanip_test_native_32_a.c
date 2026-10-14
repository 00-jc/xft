/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_native_32_a.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

static void	check_splat_native_32(void)
{
	t_nvec32	v;
	t_size		i;

	v = xft_vsplat32(5);
	i = 0;
	while (i < vmanip_n(4))
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_native_32(void)
{
	t_nvec32	v;
	t_size		i;

	v = xft_viota32();
	i = 0;
	while (i < vmanip_n(4))
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_native_32(void)
{
	t_nvec32	v;
	t_size		i;

	v = xft_vsplat32(0);
	i = 1;
	while (i < vmanip_n(4))
	{
		v[i] = (t_u32)1 << 31;
		i += 2;
	}
	xft_pin_invariant(xft_vmask32(v) == vmanip_odd(vmanip_n(4)));
	xft_pin_invariant(xft_vmask32(xft_vsplat32(1)) == 0);
}

void	test_vmanip_native_32_a(void)
{
	check_splat_native_32();
	check_iota_native_32();
	check_mask_native_32();
}
