/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_arena_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:45:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_arena.h"
#include "xft_p_hugepage.h"

__attribute__((__const__, __always_inline__))
static inline t_u32a	xft_arena_invalid_request(t_size size, t_size align)
{
	return (align == 0 || size == 0
		|| (align & (align - 1)) != 0
		|| size > HUGEPAGE_16GB - sizeof(t_hugepage) - (align - 1));
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_any	xft_arena_reserve(t_arena *restrict const allocator,
	t_size size, t_size align, t_size pagesize)
{
	t_any	next_ptr;
	int		pageflag;

	next_ptr = get_next_ptr(allocator->current, align);
	if ((t_u8 *)next_ptr + size <= allocator->current->data
		+ allocator->current->total)
		return (next_ptr);
	pageflag = xft_match_hugepage_flags(pagesize);
	if (__builtin_expect(!xft_arena_move_fwd(allocator, pagesize, pageflag),
			0))
		return (nullptr);
	return (get_next_ptr(allocator->current, align));
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline t_any	xft_arena_commit(t_arena *restrict const allocator,
	t_any next_ptr, t_size size, int pageflag)
{
	t_size	waste;

	if (__builtin_expect(!xft_mmap_commit(next_ptr, size,
				PROT_READ | PROT_WRITE, pageflag), 0))
		return (nullptr);
	waste = (t_size)((t_u8 *)next_ptr - (allocator->current->data
				+ allocator->current->used));
	allocator->current->used += waste + size;
	return (next_ptr);
}

__attribute__((__nonnull__(1)))
t_any	xft_arena_alloc(t_arena *restrict const allocator,
	t_size size, t_size align)
{
	t_any	next_ptr;
	t_size	pagesize;

	if (__builtin_expect(xft_arena_invalid_request(size, align), 0))
		return (nullptr);
	pagesize = xft_match_paging(size + align - 1);
	next_ptr = xft_arena_reserve(allocator, size, align, pagesize);
	if (__builtin_expect(!next_ptr, 0))
		return (nullptr);
	return (xft_arena_commit(allocator, next_ptr, size,
			xft_match_hugepage_flags(pagesize)));
}
