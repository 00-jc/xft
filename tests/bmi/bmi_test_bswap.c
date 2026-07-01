/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmi_test_bswap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/bmi/bmi_test.h"

void	test_bswap(void)
{
	ft_pin_invariant(ft_bswap16(0x0102) == 0x0201);
	ft_pin_invariant(ft_bswap32(0x01020304) == 0x04030201);
	ft_pin_invariant(ft_bswap64(0x0102030405060708ULL)
		== 0x0807060504030201ULL);
	ft_pin_invariant(ft_bswap16(0) == 0);
	ft_pin_invariant(ft_bswap32(0) == 0);
	ft_pin_invariant(ft_bswap64(0) == 0);
}
