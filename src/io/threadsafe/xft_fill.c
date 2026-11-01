/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/atomics.h>
#include <xft/types/io_types.h>

__attribute__((__always_inline__, __nonnull__(1, 2, 4), __used__))
inline t_result	xft_ts_stream_unbuffered_fill(t_any __restrict__ const reader,
	t_u8 *__restrict__ const dst, const t_size len,
	t_size *__restrict__ const total)
{
	t_mutex *__restrict__ const	mutex
		= ((t_reader *)reader)->as.ts_fs_reader.mutex;
	t_result					ret;

	if (mutex == nullptr)
		__builtin_unreachable();
	xft_mutex_lock(mutex, xft_lock_fast);
	ret = xft_stream_unbuffered_fill(reader, dst, len, total);
	xft_mutex_unlock(mutex);
	return (ret);
}

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_result	xft_ts_stream_fill(t_any __restrict__ const reader)
{
	t_mutex *__restrict__ const	mutex
		= ((t_reader *)reader)->as.ts_fs_reader.mutex;
	t_result					ret;

	if (mutex == nullptr)
		__builtin_unreachable();
	xft_mutex_lock(mutex, xft_lock_fast);
	ret = xft_stream_fill(reader);
	xft_mutex_unlock(mutex);
	return (ret);
}
