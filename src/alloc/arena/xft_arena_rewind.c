/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_arena_rewind.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 19:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 19:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_arena.h"

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

__attribute__((__always_inline__, __used__))
inline void	xft_arena_rewind(t_arena *restrict const arena,
	t_arena_checkpoint checkpoint)
{
	arena->current = checkpoint.location;
	arena->current->used = checkpoint.used;
}

void	xft_arena_rewind_clean(t_arena *restrict const arena,
	t_arena_checkpoint checkpoint)
{
	xft_arena_rewind(arena, checkpoint);
	xft_arena_clean_fwd(arena);
}
