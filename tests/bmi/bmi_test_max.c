/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmi_test_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/bmi/bmi_test.h"

void	test_max(void)
{
	xft_pin_invariant(xft_max_s(1, 2) == 2);
	xft_pin_invariant(xft_max_s(100, 50) == 100);
	xft_pin_invariant(xft_max_s(0, 0) == 0);
	xft_pin_invariant(xft_maxu8(10, 20) == 20);
	xft_pin_invariant(xft_maxu8(255, 0) == 255);
	xft_pin_invariant(xft_maxu32(0, 0xFFFFFFFF) == 0xFFFFFFFF);
	xft_pin_invariant(xft_maxu64(42, 42) == 42);
}
