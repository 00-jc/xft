/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_fault_native_8.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

static void	check_fault_native_8(void)
{
	t_u8	*end;
	t_nveca	l;
	t_size	i;

	end = vmanip_guard() - sizeof(t_u8);
	*end = 0x42;
	l = xft_vmask_load(end, 1);
	xft_pin_invariant(l[0] == 0x42);
	i = 1;
	while (i < XFT_NVEC_SIZE)
	{
		xft_pin_invariant(l[i] == 0);
		i++;
	}
}

void	test_vmanip_fault_native_8(void)
{
	check_fault_native_8();
}
