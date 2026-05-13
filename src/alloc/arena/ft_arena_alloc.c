/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_arena.h"

t_arena	ft_new_arena_alloc(void)
{
	t_hugepage		*initial_page;
	size_t			pagesize;
	int				pageflag;

	pagesize = ft_match_paging(1ULL << 25);
	pageflag = ft_match_paging_flags(pagesize);
	initial_page = new_hugepage(nullptr, pagesize, pageflag);
	if (!initial_page)
		return ((t_arena){0});
	return ((t_arena){.current = initial_page});
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_arena_clean_fwd(const t_arena *restrict const alloc)
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
			ft_munmap(next, next->page_size);
			next = x;
		}
	}
}

__attribute__((__nonnull__(1)))
void	ft_destroy_arena(t_arena *alloc)
{
	t_hugepage	*x;
	t_hugepage	*next;

	ft_arena_clean_fwd(alloc);
	x = alloc->current;
	while (x)
	{
		next = x->prev;
		ft_munmap(x, x->page_size);
		x = next;
	}
	alloc->current = nullptr;
}

__attribute__((nonnull(1)))
void	*ft_arena_alloc(t_arena *restrict const allocator,
	size_t size, size_t align)
{
	void			*next_ptr;
	size_t			waste;
	size_t			pagesize;
	int				pageflag;

	if (__builtin_expect(align == 0 || size == 0
			|| (align & (align - 1)) != 0
			|| size > HUGEPAGE_16GB - sizeof(t_hugepage) - (align - 1), 0))
		return (nullptr);
	pagesize = ft_match_paging(size + align - 1);
	pageflag = ft_match_paging_flags(pagesize);
	next_ptr = get_next_ptr(allocator->current, align);
	waste = (size_t)((t_u8 *)next_ptr - (allocator->current->data
				+ allocator->current->used));
	if ((t_u8 *)next_ptr + size > allocator->current->data
		+ allocator->current->total)
	{
		if (!ft_arena_move_fwd(allocator, pagesize, pageflag))
			return (nullptr);
		next_ptr = get_next_ptr(allocator->current, align);
		waste = (size_t)((t_u8 *)next_ptr - (allocator->current->data
					+ allocator->current->used));
	}
	allocator->current->used += waste + size;
	return (next_ptr);
}
