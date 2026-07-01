/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmi_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/bmi/bmi_test.h"

void	test_bmi(t_test *t)
{
	ft_test_print(t, "Testing bmi...\n");
	test_ctz();
	test_clz();
	test_bswap();
	test_max();
	ft_test_print(t, "  bmi: OK\n");
}
