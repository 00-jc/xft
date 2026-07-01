/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memchr/memchr_test.h"

void	test_memchr(t_test *t)
{
	ft_test_print(t, "Testing ft_memchr...\n");
	test_memchr_basic();
	test_memchr_edge();
	test_memchr_misaligned();
	test_memchr_long();
	ft_test_print(t, "  ft_memchr: OK\n");
}
