/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_arena_alloc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:35:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_arena.h>
#include <xft/xft_p_hugepage.h>

__attribute__((const, __always_inline__, __used__))
inline t_size	xft_match_paging(t_size requested_size)
{
	requested_size += sizeof(t_hugepage);
	return (xft_tern_s(requested_size < HUGEPAGE_256MB, HUGEPAGE_256MB,
			requested_size));
}

__attribute__((__nonnull__(1), __returns_nonnull__, __always_inline__))
__attribute__((__used__))
inline t_any	get_next_ptr(t_hugepage *page, t_size align)
{
	t_any	addr;
	t_u8	*base;

	base = page->data + page->used;
	addr = xft_align_fwd(base, align);
	return (addr);
}

__attribute__((__always_inline__, __used__))
inline t_hugepage	*new_hugepage(t_hugepage *restrict const prev, t_size size)
{
	t_hugepage	*page;
	t_buffer	b;

	if (prev && prev->next && prev->next->page_size >= size)
		return ((void)(page = prev->next), (void)(page->used = 0), page);
	b = xft_palloc_reserve(size);
	if (!b.mem)
		return (nullptr);
	if (!xft_palloc_commit(b.mem, sizeof(t_hugepage)))
		return (xft_palloc_free(b), nullptr);
	page = (t_hugepage *)b.mem;
	*page = (t_hugepage){.page_size = b.size, .prev = prev,
		.total = b.size - sizeof(t_hugepage)};
	if (prev && prev->next)
	{
		page->next = prev->next;
		page->next->prev = page;
	}
	if (prev)
		prev->next = page;
	return (page);
}

__attribute__((__nonnull__(1)))
t_u32a	xft_arena_move_fwd(t_arena *alloc, t_size size)
{
	t_hugepage	*old;

	old = alloc->current;
	alloc->current = new_hugepage(old, size);
	if (!alloc->current)
	{
		alloc->current = old;
		return (0);
	}
	return (1);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_u32a	xft_arena_try_resize(t_hugepage *page, t_buffer old,
	t_size new_size)
{
	t_u8	*top;

	top = page->data + page->used;
	if (old.mem + old.size != top
		|| new_size > (t_size)(page->data + page->total - old.mem))
		return (0);
	if (new_size > old.size
		&& !xft_palloc_commit(top, new_size - old.size))
		return (0);
	page->used = (t_size)(old.mem + new_size - page->data);
	return (1);
}
