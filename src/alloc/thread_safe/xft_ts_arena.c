/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_ts_arena.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 14:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 14:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/alloc.h>
#include <xft/atomics.h>
#include <xft/mem.h>
#include <xft/xft_p_arena.h>

t_ts_arena	xft_new_ts_arena(void)
{
	return ((t_ts_arena){.mutex = XFT_UNLOCKED, .arena = xft_new_arena()});
}

__attribute__((__nonnull__(1)))
t_buffer	xft_ts_arena_alloc(t_any alloc, t_size size, t_size align)
{
	t_any	ptr;

	xft_mutex_lock(&((t_ts_arena *)alloc)->mutex, xft_lock_fast);
	ptr = xft_arena_alloc(&((t_ts_arena *)alloc)->arena, size, align);
	xft_mutex_unlock(&((t_ts_arena *)alloc)->mutex);
	return (xft_fatptr(ptr, size));
}

__attribute__((__nonnull__(1)))
t_buffer	xft_ts_arena_realloc(t_any alloc, t_buffer buf, t_size newsize,
				t_size align)
{
	xft_mutex_lock(&((t_ts_arena *)alloc)->mutex, xft_lock_fast);
	buf = xft_arena_realloc(&((t_ts_arena *)alloc)->arena, buf, newsize,
			align);
	xft_mutex_unlock(&((t_ts_arena *)alloc)->mutex);
	return (buf);
}

__attribute__((__nonnull__(1)))
void	xft_ts_arena_free(t_any alloc, t_buffer buf)
{
	(void)alloc;
	(void)buf;
}

__attribute__((__nonnull__(1)))
void	xft_ts_arena_destroy(t_any alloc)
{
	xft_mutex_lock(&((t_ts_arena *)alloc)->mutex, xft_lock_fast);
	xft_destroy_arena(&((t_ts_arena *)alloc)->arena);
	xft_mutex_unlock(&((t_ts_arena *)alloc)->mutex);
}
