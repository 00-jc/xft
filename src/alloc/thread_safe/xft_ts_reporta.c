/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_ts_reporta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 14:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 14:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/alloc.h>
#include <xft/atomics.h>

t_ts_reporta	xft_new_ts_reporta(void)
{
	return ((t_ts_reporta){.mutex = XFT_UNLOCKED,
		.reporta = xft_new_reporta()});
}

__attribute__((__nonnull__(1)))
t_buffer	xft_ts_reporta_alloc(t_any alloc, t_size size, t_size align)
{
	t_buffer	buf;

	xft_mutex_lock(&((t_ts_reporta *)alloc)->mutex, xft_lock_fast);
	buf = xft_reporta_alloc(&((t_ts_reporta *)alloc)->reporta, size, align);
	xft_mutex_unlock(&((t_ts_reporta *)alloc)->mutex);
	return (buf);
}

__attribute__((__nonnull__(1)))
t_buffer	xft_ts_reporta_realloc(t_any alloc, t_buffer buf, t_size newsize,
				t_size align)
{
	xft_mutex_lock(&((t_ts_reporta *)alloc)->mutex, xft_lock_fast);
	buf = xft_reporta_realloc(&((t_ts_reporta *)alloc)->reporta, buf,
			newsize, align);
	xft_mutex_unlock(&((t_ts_reporta *)alloc)->mutex);
	return (buf);
}

__attribute__((__nonnull__(1)))
void	xft_ts_reporta_free(t_any alloc, t_buffer buf)
{
	xft_mutex_lock(&((t_ts_reporta *)alloc)->mutex, xft_lock_fast);
	xft_reporta_free(&((t_ts_reporta *)alloc)->reporta, buf);
	xft_mutex_unlock(&((t_ts_reporta *)alloc)->mutex);
}

__attribute__((__nonnull__(1)))
void	xft_ts_reporta_destroy(t_any alloc)
{
	xft_mutex_lock(&((t_ts_reporta *)alloc)->mutex, xft_lock_fast);
	xft_reporta_destroy(&((t_ts_reporta *)alloc)->reporta);
	xft_mutex_unlock(&((t_ts_reporta *)alloc)->mutex);
}
