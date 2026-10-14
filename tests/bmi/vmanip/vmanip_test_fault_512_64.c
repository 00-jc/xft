/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_fault_512_64.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

#if XFT_HAS_512_VEC

static void	check_fault_512_64(void)
{
	t_u8		*end;
	t_vu64_512a	l;
	t_size		i;

	end = vmanip_guard() - sizeof(t_u64);
	*(t_u64 *)end = 0x42;
	l = xft_vmask_load512_64(end, 1);
	xft_pin_invariant(l[0] == 0x42);
	i = 1;
	while (i < 8)
	{
		xft_pin_invariant(l[i] == 0);
		i++;
	}
}

void	test_vmanip_fault_512_64(void)
{
	check_fault_512_64();
}

#else

void	test_vmanip_fault_512_64(void)
{
}

#endif
