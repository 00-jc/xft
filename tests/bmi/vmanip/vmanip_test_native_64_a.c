/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_native_64_a.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

static void	check_splat_native_64(void)
{
	t_nvec64	v;
	t_size		i;

	v = xft_vsplat64(5);
	i = 0;
	while (i < vmanip_n(8))
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_native_64(void)
{
	t_nvec64	v;
	t_size		i;

	v = xft_viota64();
	i = 0;
	while (i < vmanip_n(8))
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_native_64(void)
{
	t_nvec64	v;
	t_size		i;

	v = xft_vsplat64(0);
	i = 1;
	while (i < vmanip_n(8))
	{
		v[i] = (t_u64)1 << 63;
		i += 2;
	}
	xft_pin_invariant(xft_vmask64(v) == vmanip_odd(vmanip_n(8)));
	xft_pin_invariant(xft_vmask64(xft_vsplat64(1)) == 0);
}

void	test_vmanip_native_64_a(void)
{
	check_splat_native_64();
	check_iota_native_64();
	check_mask_native_64();
}
