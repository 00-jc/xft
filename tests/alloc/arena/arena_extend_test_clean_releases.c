/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_extend_test_clean_releases.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_extend_test.h"

void	test_extend_clean_releases(void)
{
	t_arena				a;
	t_arena_checkpoint	cp;
	t_hugepage			*base;
	t_size				big;
	int					i;

	a = xft_new_arena();
	base = a.current;
	cp = xft_arena_checkpoint(&a);
	big = base->total - base->used - 128;
	xft_arena_alloc(&a, big, 16);
	i = -1;
	while (++i < 4)
		xft_arena_alloc(&a, 4096, 16);
	xft_arena_rewind_clean(&a, cp);
	xft_pin_invariant_msg(a.current == base,
		xft_fatptr((t_u8 *)"back to base", sizeof("back to base") - 1));
	xft_pin_invariant_msg(base->next == nullptr,
		xft_fatptr((t_u8 *)"chain cleared", sizeof("chain cleared") - 1));
	xft_pin_invariant_msg(xft_arena_alloc(&a, 64, 8) != nullptr,
		xft_fatptr((t_u8 *)"alloc after clean",
			sizeof("alloc after clean") - 1));
	xft_destroy_arena(&a);
}
