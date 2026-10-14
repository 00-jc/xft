/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_native_16_a.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

static void	check_splat_native_16(void)
{
	t_nvec16	v;
	t_size		i;

	v = xft_vsplat16(5);
	i = 0;
	while (i < vmanip_n(2))
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_native_16(void)
{
	t_nvec16	v;
	t_size		i;

	v = xft_viota16();
	i = 0;
	while (i < vmanip_n(2))
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_native_16(void)
{
	t_nvec16	v;
	t_size		i;

	v = xft_vsplat16(0);
	i = 1;
	while (i < vmanip_n(2))
	{
		v[i] = (t_u16)1 << 15;
		i += 2;
	}
	xft_pin_invariant(xft_vmask16(v) == vmanip_odd(vmanip_n(2)));
	xft_pin_invariant(xft_vmask16(xft_vsplat16(1)) == 0);
}

void	test_vmanip_native_16_a(void)
{
	check_splat_native_16();
	check_iota_native_16();
	check_mask_native_16();
}
