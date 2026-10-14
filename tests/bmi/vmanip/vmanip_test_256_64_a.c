/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_256_64_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_256_VEC

static void	check_splat_256_64(void)
{
	t_vu64_256	v;
	t_size		i;

	v = xft_vsplat256_64(5);
	i = 0;
	while (i < 4)
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_256_64(void)
{
	t_vu64_256	v;
	t_size		i;

	v = xft_viota256_64();
	i = 0;
	while (i < 4)
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_256_64(void)
{
	t_vu64_256	v;
	t_size		i;

	v = xft_vsplat256_64(0);
	i = 1;
	while (i < 4)
	{
		v[i] = (t_u64)1 << 63;
		i += 2;
	}
	xft_pin_invariant(xft_vmask256_64(v) == vmanip_odd(4));
	xft_pin_invariant(xft_vmask256_64(xft_vsplat256_64(1)) == 0);
}

void	test_vmanip_256_64_a(void)
{
	check_splat_256_64();
	check_iota_256_64();
	check_mask_256_64();
}

#else

void	test_vmanip_256_64_a(void)
{
}

#endif
