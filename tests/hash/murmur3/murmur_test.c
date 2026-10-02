/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murmur_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/hash/murmur3/murmur_test.h"

void	test_murmur(t_test *t)
{
	xft_test_print(t, "Testing xft_murmur3...\n");
	test_murmur_deterministic();
	test_murmur_diff_input();
	test_murmur_seed();
	test_murmur_lengths();
	xft_test_print(t, "  xft_murmur3: OK\n");
}
