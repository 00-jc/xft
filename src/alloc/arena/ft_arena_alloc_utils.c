/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena_alloc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_arena.h"

__attribute__((const, __always_inline__))
inline size_t	ft_match_paging(size_t requested_size)
{
	size_t	page_size;
	size_t	policy;

	policy = requested_size + sizeof(t_hugepage);
	page_size = -(policy <= HUGEPAGE_16GB) & HUGEPAGE_16GB;
	page_size = (-(policy <= HUGEPAGE_2GB) & HUGEPAGE_2GB)
		| (-(policy > HUGEPAGE_2GB) & page_size);
	page_size = (-(policy <= HUGEPAGE_1GB) & HUGEPAGE_1GB)
		| (-(policy > HUGEPAGE_1GB) & page_size);
	page_size = (-(policy <= HUGEPAGE_512MB) & HUGEPAGE_512MB)
		| (-(policy > HUGEPAGE_512MB) & page_size);
	page_size = (-(policy <= HUGEPAGE_256MB) & HUGEPAGE_256MB)
		| (-(policy > HUGEPAGE_256MB) & page_size);
	return (page_size);
}

__attribute__((const, __always_inline__))
inline int	ft_match_paging_flags(size_t page_size)
{
	t_u32	flags;

	flags = -(page_size == HUGEPAGE_2MB) & MAP_HUGE_2MB;
	flags |= -(page_size == HUGEPAGE_16MB) & MAP_HUGE_16MB;
	flags |= -(page_size == HUGEPAGE_256MB) & MAP_HUGE_256MB;
	flags |= -(page_size == HUGEPAGE_512MB) & MAP_HUGE_512MB;
	flags |= -(page_size == HUGEPAGE_1GB) & MAP_HUGE_1GB;
	flags |= -(page_size == HUGEPAGE_2GB) & MAP_HUGE_2GB;
	flags |= -(page_size == HUGEPAGE_16GB) & MAP_HUGE_16GB;
	return ((int)flags);
}

__attribute__((nonnull(1), returns_nonnull, __always_inline__))
inline void	*get_next_ptr(t_hugepage *page, size_t align)
{
	void	*addr;
	t_u8	*base;
	size_t	align_overhead;

	base = page->data + page->used;
	align_overhead = align - 1;
	addr = (void *)(((t_uptr)base + (align_overhead)) & ~(align_overhead));
	return (addr);
}

t_hugepage	*new_hugepage(t_hugepage *restrict const prev,
	size_t size, int flag)
{
	t_hugepage	*page;

	if (prev && prev->next && prev->next->page_size >= size)
		return ((void)(page = prev->next), (void)(page->used = 0), page);
	page = ft_mmap(size, 0, flag);
	if (page == MAP_FAILED)
		return (nullptr);
	page->page_size = size;
	page->prev = prev;
	page->total = size - sizeof(t_hugepage);
	page->used = 0;
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

__attribute__((nonnull(1)))
t_u32a	ft_arena_move_fwd(t_arena *alloc, size_t size, int flag)
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
