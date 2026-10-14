/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmanip_test_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tests/bmi/vmanip_test.h"

t_size	vmanip_n(t_size bytes)
{
	return (XFT_NVEC_SIZE / bytes);
}

t_u8	*vmanip_guard(void)
{
	static t_u8	*base;

	if (base == NULL)
	{
		base = xft_mmap(8192, PROT_READ | PROT_WRITE, 0);
		xft_mprotect(base + 4096, 4096, PROT_NONE);
	}
	return (base + 4096);
}

t_u64	vmanip_lane(t_size i, t_size n)
{
	if (i >= n / 2)
		return (0);
	return (2 * i + 1);
}
