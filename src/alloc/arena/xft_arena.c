/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 19:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 01:33:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_arena.h>
#include <xft/xft_p_hugepage.h>

__attribute__((__nonnull__(1)))
t_result	xft_new_arena(t_arena *arena)
{
	t_hugepage		*initial_page;

	initial_page = new_hugepage(nullptr, xft_match_paging(1ULL << 25));
	if (__builtin_expect(initial_page == nullptr, 0))
		return ((t_result){.ok = KO, .err = xft_err_oom});
	*arena = (t_arena){.current = initial_page};
	return ((t_result){.ok = OK});
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
		xft_palloc_free(xft_fatptr((t_any)x, x->page_size));
		x = next;
	}
	alloc->current = nullptr;
}
