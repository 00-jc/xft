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
	ft_pin_invariant(ft_max_s(1, 2) == 2);
	ft_pin_invariant(ft_max_s(100, 50) == 100);
	ft_pin_invariant(ft_max_s(0, 0) == 0);
	ft_pin_invariant(ft_maxu8(10, 20) == 20);
	ft_pin_invariant(ft_maxu8(255, 0) == 255);
	ft_pin_invariant(ft_maxu32(0, 0xFFFFFFFF) == 0xFFFFFFFF);
	ft_pin_invariant(ft_maxu64(42, 42) == 42);
}
