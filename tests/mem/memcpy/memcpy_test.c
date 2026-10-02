/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memcpy/memcpy_test.h"

void	test_memcpy(t_test *t)
{
	xft_test_print(t, "Testing xft_memcpy...\n");
	test_memcpy_basic();
	test_memcpy_misaligned();
	test_memcpy_large();
	xft_test_print(t, "  xft_memcpy: OK\n");
}
