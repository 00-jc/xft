/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_128_64_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_128_VEC

static void	check_splat_128_64(void)
{
	t_vu64_128	v;
	t_size		i;

	v = xft_vsplat128_64(5);
	i = 0;
	while (i < 2)
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_128_64(void)
{
	t_vu64_128	v;
	t_size		i;

	v = xft_viota128_64();
	i = 0;
	while (i < 2)
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_128_64(void)
{
	t_vu64_128	v;
	t_size		i;

	v = xft_vsplat128_64(0);
	i = 1;
	while (i < 2)
	{
		v[i] = (t_u64)1 << 63;
		i += 2;
	}
	xft_pin_invariant(xft_vmask128_64(v) == vmanip_odd(2));
	xft_pin_invariant(xft_vmask128_64(xft_vsplat128_64(1)) == 0);
}

void	test_vmanip_128_64_a(void)
{
	check_splat_128_64();
	check_iota_128_64();
	check_mask_128_64();
}

#else

void	test_vmanip_128_64_a(void)
{
}

#endif
