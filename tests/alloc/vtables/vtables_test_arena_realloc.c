/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test_arena_realloc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

__attribute__((__nonnull__(1)))
static void	arena_test_move(t_allocator *alloc, t_buffer buf)
{
	t_buffer	rbuf;

	buf.mem[0] = 0xDE;
	buf.mem[15] = 0xAD;
	rbuf = alloc->vtable.realloc(alloc->allocator, buf, 128, 8);
	xft_pin_invariant_msg(rbuf.mem != buf.mem && rbuf.size == 128,
		xft_fatptr((t_u8 *)"arena: mid grow moves",
			sizeof("arena: mid grow moves") - 1));
	xft_pin_invariant_msg(rbuf.mem[0] == 0xDE && rbuf.mem[15] == 0xAD,
		xft_fatptr((t_u8 *)"arena: mid grow data",
			sizeof("arena: mid grow data") - 1));
	alloc->vtable.allocate(alloc->allocator, 1, 4096);
	buf = alloc->vtable.allocate(alloc->allocator, 16, 16);
	rbuf = alloc->vtable.realloc(alloc->allocator, buf, 32, 4096);
	xft_pin_invariant_msg(rbuf.mem != buf.mem
		&& ((t_uptr)rbuf.mem & 4095) == 0,
		xft_fatptr((t_u8 *)"arena: realign moves",
			sizeof("arena: realign moves") - 1));
}

__attribute__((__nonnull__(1)))
static void	arena_test_shrink(t_allocator *alloc, t_buffer buf)
{
	t_arena		*arena;
	t_buffer	rbuf;
	t_size		used;

	arena = (t_arena *)alloc->allocator;
	used = arena->current->used;
	rbuf = alloc->vtable.realloc(alloc->allocator, buf, 32, 8);
	xft_pin_invariant_msg(rbuf.mem == buf.mem && rbuf.size == 32,
		xft_fatptr((t_u8 *)"arena: shrink in place",
			sizeof("arena: shrink in place") - 1));
	xft_pin_invariant_msg(arena->current->used == used - 32,
		xft_fatptr((t_u8 *)"arena: shrink gives tail",
			sizeof("arena: shrink gives tail") - 1));
	alloc->vtable.allocate(alloc->allocator, 8, 8);
	used = arena->current->used;
	buf = alloc->vtable.realloc(alloc->allocator, rbuf, 16, 8);
	xft_pin_invariant_msg(buf.mem == rbuf.mem && arena->current->used == used,
		xft_fatptr((t_u8 *)"arena: mid shrink in place",
			sizeof("arena: mid shrink in place") - 1));
	arena_test_move(alloc, buf);
}

__attribute__((__nonnull__(1)))
void	test_arena_vtable_realloc(t_allocator *alloc, t_buffer buf)
{
	t_buffer	rbuf;

	rbuf = alloc->vtable.realloc(alloc->allocator, buf, 256, 16);
	xft_pin_invariant_msg(rbuf.mem != nullptr,
		xft_fatptr((t_u8 *)"arena: realloc ok",
			sizeof("arena: realloc ok") - 1));
	xft_pin_invariant_msg(rbuf.size == 256,
		xft_fatptr((t_u8 *)"arena: realloc size",
			sizeof("arena: realloc size") - 1));
	xft_pin_invariant_msg(rbuf.mem == buf.mem,
		xft_fatptr((t_u8 *)"arena: grow in place",
			sizeof("arena: grow in place") - 1));
	xft_pin_invariant_msg(rbuf.mem[0] == 0xDE,
		xft_fatptr((t_u8 *)"arena: rdata lo", sizeof("arena: rdata lo") - 1));
	xft_pin_invariant_msg(rbuf.mem[127] == 0xAD,
		xft_fatptr((t_u8 *)"arena: rdata hi", sizeof("arena: rdata hi") - 1));
	alloc->vtable.free(alloc->allocator, rbuf);
	rbuf = alloc->vtable.allocate(alloc->allocator, 64, 8);
	xft_pin_invariant_msg(rbuf.mem != nullptr,
		xft_fatptr((t_u8 *)"arena: post-free alloc",
			sizeof("arena: post-free alloc") - 1));
	arena_test_shrink(alloc, rbuf);
	alloc->vtable.destroy(alloc->allocator);
}
