/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena_alloc_scopes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_arena.h"

__attribute__((__always_inline__))
inline void	ft_arena_rewind(t_arena *restrict const arena,
	t_arena_checkpoint checkpoint)
{
	arena->current = checkpoint.location;
	arena->current->used = checkpoint.used;
}

void	ft_arena_rewind_clean(t_arena *restrict const arena,
	t_arena_checkpoint checkpoint)
{
	ft_arena_rewind(arena, checkpoint);
	ft_arena_clean_fwd(arena);
}

__attribute__((__nonnull__(1), pure, __always_inline__))
inline t_arena_checkpoint	ft_arena_checkpoint(
	const t_arena *restrict const arena)
{
	return ((t_arena_checkpoint)
		{
			.used = arena->current->used,
			.location = arena->current,
		});
}
