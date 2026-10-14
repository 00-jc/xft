/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_512_64_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_512_VEC

static void	check_splat_512_64(void)
{
	t_vu64_512	v;
	t_size		i;

	v = xft_vsplat512_64(5);
	i = 0;
	while (i < 8)
	{
		xft_pin_invariant(v[i] == 5);
		i++;
	}
}

static void	check_iota_512_64(void)
{
	t_vu64_512	v;
	t_size		i;

	v = xft_viota512_64();
	i = 0;
	while (i < 8)
	{
		xft_pin_invariant(v[i] == i);
		i++;
	}
}

static void	check_mask_512_64(void)
{
	t_vu64_512	v;
	t_size		i;

	v = xft_vsplat512_64(0);
	i = 1;
	while (i < 8)
	{
		v[i] = (t_u64)1 << 63;
		i += 2;
	}
	xft_pin_invariant(xft_vmask512_64(v) == vmanip_odd(8));
	xft_pin_invariant(xft_vmask512_64(xft_vsplat512_64(1)) == 0);
}

void	test_vmanip_512_64_a(void)
{
	check_splat_512_64();
	check_iota_512_64();
	check_mask_512_64();
}

#else

void	test_vmanip_512_64_a(void)
{
}

#endif
