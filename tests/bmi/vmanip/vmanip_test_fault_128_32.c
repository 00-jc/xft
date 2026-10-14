/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_fault_128_32.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_128_VEC

static void	check_fault_128_32(void)
{
	t_u8		*end;
	t_vu32_128a	l;
	t_size		i;

	end = vmanip_guard() - sizeof(t_u32);
	*(t_u32 *)end = 0x42;
	l = xft_vmask_load128_32(end, 1);
	xft_pin_invariant(l[0] == 0x42);
	i = 1;
	while (i < 4)
	{
		xft_pin_invariant(l[i] == 0);
		i++;
	}
}

void	test_vmanip_fault_128_32(void)
{
	check_fault_128_32();
}

#else

void	test_vmanip_fault_128_32(void)
{
}

#endif
