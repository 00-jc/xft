/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_ts_gpa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 14:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 14:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/alloc.h>
#include <xft/atomics.h>

t_ts_gpa	xft_new_ts_gpa(void)
{
	return ((t_ts_gpa){.mutex = xft_unlocked, .gpa = xft_new_gpa()});
}

__attribute__((__flatten__, __nonnull__(1)))
t_buffer	xft_ts_gpa_alloc(t_any alloc, t_size size, t_size align)
{
	t_buffer	buf;

	xft_mutex_lock(&((t_ts_gpa *)alloc)->mutex, xft_lock_fast);
	buf = xft_gpa_alloc(&((t_ts_gpa *)alloc)->gpa, size, align);
	xft_mutex_unlock(&((t_ts_gpa *)alloc)->mutex);
	return (buf);
}

__attribute__((__flatten__, __nonnull__(1)))
t_buffer	xft_ts_gpa_realloc(t_any alloc, t_buffer buf, t_size newsize,
				t_size align)
{
	xft_mutex_lock(&((t_ts_gpa *)alloc)->mutex, xft_lock_fast);
	buf = xft_gpa_realloc(&((t_ts_gpa *)alloc)->gpa, buf, newsize, align);
	xft_mutex_unlock(&((t_ts_gpa *)alloc)->mutex);
	return (buf);
}

__attribute__((__flatten__, __nonnull__(1)))
void	xft_ts_gpa_free(t_any alloc, t_buffer buf)
{
	xft_mutex_lock(&((t_ts_gpa *)alloc)->mutex, xft_lock_fast);
	xft_gpa_free(&((t_ts_gpa *)alloc)->gpa, buf);
	xft_mutex_unlock(&((t_ts_gpa *)alloc)->mutex);
}

__attribute__((__flatten__, __nonnull__(1)))
void	xft_ts_gpa_destroy(t_any alloc)
{
	xft_mutex_lock(&((t_ts_gpa *)alloc)->mutex, xft_lock_fast);
	xft_gpa_destroy(&((t_ts_gpa *)alloc)->gpa);
	xft_mutex_unlock(&((t_ts_gpa *)alloc)->mutex);
}
