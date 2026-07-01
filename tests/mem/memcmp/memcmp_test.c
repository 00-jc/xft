/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memcmp/memcmp_test.h"

void	test_memcmp(t_test *t)
{
	ft_test_print(t, "Testing ft_memcmp...\n");
	test_memcmp_basic();
	test_memcmp_binary();
	test_memcmp_long();
	test_memcmp_misaligned();
	ft_test_print(t, "  ft_memcmp: OK\n");
}
