/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmi_test_clz.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/bmi/bmi_test.h"

void	test_clz(void)
{
	xft_pin_invariant(xft_memclz_u32(1) == 31);
	xft_pin_invariant(xft_memclz_u32(2) == 30);
	xft_pin_invariant(xft_memclz_u32(0x80000000U) == 0);
	xft_pin_invariant(xft_memclz_u32(0xFF) == 24);
	xft_pin_invariant(xft_memclz_u64(1) == 63);
	xft_pin_invariant(xft_memclz_u64(0x8000000000000000ULL) == 0);
	xft_pin_invariant(xft_memclz_u16(1) == 15);
	xft_pin_invariant(xft_memclz_u16(0x8000) == 0);
}
