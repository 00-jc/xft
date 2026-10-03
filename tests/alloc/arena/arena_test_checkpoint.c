/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_test_checkpoint.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_test.h"

void	test_arena_checkpoint(void)
{
	t_arena				a;
	t_arena_checkpoint	cp;
	t_any				p1;
	t_any				p2;
	t_any				p3;

	a = xft_new_arena();
	p1 = xft_arena_alloc(&a, 64, 8);
	cp = xft_arena_checkpoint(&a);
	p2 = xft_arena_alloc(&a, 128, 8);
	xft_pin_invariant_msg(p2 != nullptr,
		xft_fatptr((t_u8 *)"after cp", sizeof("after cp") - 1));
	xft_arena_rewind(&a, cp);
	p3 = xft_arena_alloc(&a, 128, 8);
	xft_pin_invariant_msg(p3 == p2,
		xft_fatptr((t_u8 *)"rewind addr", sizeof("rewind addr") - 1));
	(void)p1;
	xft_arena_rewind_clean(&a, cp);
	p3 = xft_arena_alloc(&a, 64, 8);
	xft_pin_invariant_msg(p3 != nullptr,
		xft_fatptr((t_u8 *)"after clean", sizeof("after clean") - 1));
	xft_destroy_arena(&a);
}
