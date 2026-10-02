/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_arena_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_arena.h"
#include "xft_p_hugepage.h"

t_arena	xft_new_arena_alloc(void)
{
	t_hugepage		*initial_page;
	t_size			pagesize;
	int				pageflag;

	pagesize = xft_match_paging(1ULL << 25);
	pageflag = xft_match_hugepage_flags(pagesize);
	initial_page = new_hugepage(nullptr, pagesize, pageflag);
	if (!initial_page)
		return ((t_arena){0});
	return ((t_arena){.current = initial_page});
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_arena_clean_fwd(const t_arena *restrict const alloc)
{
	t_hugepage	*x;
	t_hugepage	*next;

	if (alloc->current)
	{
		next = alloc->current->next;
		alloc->current->next = nullptr;
		while (next)
		{
			x = next->next;
			xft_munmap(next, next->page_size);
			next = x;
		}
	}
}

__attribute__((__nonnull__(1)))
void	xft_destroy_arena(t_arena *alloc)
{
	t_hugepage	*x;
	t_hugepage	*next;

	xft_arena_clean_fwd(alloc);
	x = alloc->current;
	while (x)
	{
		next = x->prev;
		xft_munmap(x, x->page_size);
		x = next;
	}
	alloc->current = nullptr;
}

__attribute__((__nonnull__(1)))
t_any	xft_arena_alloc(t_arena *restrict const allocator,
	t_size size, t_size align)
{
	t_any			next_ptr;
	t_size			waste;
	t_size			pagesize;
	int				pageflag;

	if (__builtin_expect(align == 0 || size == 0
			|| (align & (align - 1)) != 0
			|| size > HUGEPAGE_16GB - sizeof(t_hugepage) - (align - 1), 0))
		return (nullptr);
	pagesize = xft_match_paging(size + align - 1);
	pageflag = xft_match_hugepage_flags(pagesize);
	next_ptr = get_next_ptr(allocator->current, align);
	waste = (t_size)((t_u8 *)next_ptr - (allocator->current->data
				+ allocator->current->used));
	if ((t_u8 *)next_ptr + size > allocator->current->data
		+ allocator->current->total)
	{
		if (!xft_arena_move_fwd(allocator, pagesize, pageflag))
			return (nullptr);
		next_ptr = get_next_ptr(allocator->current, align);
		waste = (t_size)((t_u8 *)next_ptr - (allocator->current->data
					+ allocator->current->used));
	}
	allocator->current->used += waste + size;
	return (next_ptr);
}
