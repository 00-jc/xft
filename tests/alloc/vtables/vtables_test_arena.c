/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test_arena.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

void	test_arena_vtable(void)
{
	t_arena		arena;
	t_allocator	alloc;
	t_buffer	buf;

	arena = xft_new_arena();
	alloc = xft_arena_allocator(&arena);
	buf = alloc.vtable.allocate(alloc.allocator, 128, 16);
	xft_pin_invariant_msg(buf.mem != nullptr,
		xft_fatptr((t_u8 *)"arena: alloc non-null",
			sizeof("arena: alloc non-null") - 1));
	xft_pin_invariant_msg(buf.size == 128,
		xft_fatptr((t_u8 *)"arena: alloc size",
			sizeof("arena: alloc size") - 1));
	xft_pin_invariant_msg(((t_uptr)buf.mem & 15) == 0,
		xft_fatptr((t_u8 *)"arena: align", sizeof("arena: align") - 1));
	buf.mem[0] = 0xDE;
	buf.mem[127] = 0xAD;
	test_arena_vtable_realloc(&alloc, buf);
}
