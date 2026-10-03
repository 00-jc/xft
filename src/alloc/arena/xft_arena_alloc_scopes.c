/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_arena_alloc_scopes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 19:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_arena.h"

__attribute__((__nonnull__(1), pure, __always_inline__, __used__))
inline t_arena_checkpoint	xft_arena_checkpoint(
	const t_arena *restrict const arena)
{
	return ((t_arena_checkpoint)
		{
			.used = arena->current->used,
			.location = arena->current,
		});
}
