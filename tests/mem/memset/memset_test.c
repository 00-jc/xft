/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memset/memset_test.h"

void	test_memset(t_test *t)
{
	xft_test_print(t, "Testing xft_memset (SIMD)...\n");
	test_memset_basic();
	test_memset_large();
	test_memset_misaligned();
	xft_test_print(t, "  xft_memset: OK\n");
}
