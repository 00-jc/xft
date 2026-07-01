/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmi_test_ctz.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/bmi/bmi_test.h"

void	test_ctz(void)
{
	ft_pin_invariant(ft_memctz_u32(1) == 0);
	ft_pin_invariant(ft_memctz_u32(2) == 1);
	ft_pin_invariant(ft_memctz_u32(4) == 2);
	ft_pin_invariant(ft_memctz_u32(0x80) == 7);
	ft_pin_invariant(ft_memctz_u32(0x80000000U) == 31);
	ft_pin_invariant(ft_memctz_u64(1) == 0);
	ft_pin_invariant(ft_memctz_u64(0x100) == 8);
	ft_pin_invariant(ft_memctz_u64(0x8000000000000000ULL) == 63);
	ft_pin_invariant(ft_memctz_u16(1) == 0);
	ft_pin_invariant(ft_memctz_u16(0x8000) == 15);
}
