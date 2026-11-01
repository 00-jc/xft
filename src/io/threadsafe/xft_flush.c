/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_flush.c                                        :+:      :+:    :+:   */
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

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_result	xft_ts_stream_flush(t_any __restrict__ const writer)
{
	t_mutex *__restrict__ const	mutex
		= ((t_writer *)writer)->as.ts_fs_writer.mutex;
	t_result					ret;

	if (mutex == nullptr)
		__builtin_unreachable();
	xft_mutex_lock(mutex, xft_lock_fast);
	ret = xft_stream_flush(writer);
	xft_mutex_unlock(mutex);
	return (ret);
}
