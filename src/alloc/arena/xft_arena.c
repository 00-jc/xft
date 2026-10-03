/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 19:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 19:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_arena.h"
#include "xft_p_hugepage.h"

t_arena	xft_new_arena(void)
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
