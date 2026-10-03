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

#include "xft_p_arena.h"
#include "xft_p_hugepage.h"

__attribute__((const, __always_inline__, __used__))
inline t_size	xft_match_paging(t_size requested_size)
{
	t_size	page_size;

	page_size = xft_match_hugepage(requested_size + sizeof(t_hugepage));
	return (xft_tern(page_size < HUGEPAGE_256MB, HUGEPAGE_256MB, page_size));
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
inline t_hugepage	*new_hugepage(t_hugepage *restrict const prev,
	t_size size, int flag)
{
	t_hugepage	*page;

	if (prev && prev->next && prev->next->page_size >= size)
		return ((void)(page = prev->next), (void)(page->used = 0), page);
	page = xft_mmap(size, PROT_READ | PROT_WRITE, flag);
	if (xft_map_failed(page))
		return (nullptr);
	if (!xft_mmap_commit(page, sizeof(t_hugepage), PROT_READ | PROT_WRITE, 0))
		return (xft_munmap(page, size), nullptr);
	*page = (t_hugepage){.page_size = size, .prev = prev,
		.total = size - sizeof(t_hugepage)};
	if (prev && prev->next)
	{
		page->next = prev->next;
		page->next->prev = page;
		prev->next = page;
	}
	else
	{
		page->next = nullptr;
		if (prev)
			prev->next = page;
	}
	return (page);
}

__attribute__((__nonnull__(1)))
t_u32a	xft_arena_move_fwd(t_arena *alloc, t_size size, int flag)
{
	t_hugepage	*old;

	old = alloc->current;
	alloc->current = new_hugepage(old, size, flag);
	if (!alloc->current)
	{
		alloc->current = old;
		return (0);
	}
	return (1);
}
