/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xoshiro_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/rng/xoshiro/xoshiro_test.h"

void	test_xoshiro(t_test *t)
{
	xft_test_print(t, "Testing xft_xoshiro256**...\n");
	test_xoshiro_basic();
	test_xoshiro_not_constant();
	test_xoshiro_state_changes();
	test_xoshiro_init_diff();
	xft_test_print(t, "  xft_xoshiro256**: OK\n");
}
