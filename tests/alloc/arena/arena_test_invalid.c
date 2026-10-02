/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_test_invalid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_test.h"

void	test_arena_invalid(void)
{
	t_arena	a;

	a = xft_new_arena_alloc();
	xft_pin_invariant_msg(xft_arena_alloc(&a, 16, 0) == nullptr,
		xft_fatptr((t_u8 *)"align 0", sizeof("align 0") - 1));
	xft_pin_invariant_msg(xft_arena_alloc(&a, 16, 3) == nullptr,
		xft_fatptr((t_u8 *)"align 3", sizeof("align 3") - 1));
	xft_pin_invariant_msg(xft_arena_alloc(&a, 16, 6) == nullptr,
		xft_fatptr((t_u8 *)"align 6", sizeof("align 6") - 1));
	xft_pin_invariant_msg(xft_arena_alloc(&a, 0, 8) == nullptr,
		xft_fatptr((t_u8 *)"size 0", sizeof("size 0") - 1));
	xft_pin_invariant_msg(xft_arena_alloc(&a, (t_size)-1, 8) == nullptr,
		xft_fatptr((t_u8 *)"oversize", sizeof("oversize") - 1));
	xft_destroy_arena(&a);
}
