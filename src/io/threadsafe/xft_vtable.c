/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_vtable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>
#include <xft/xft_p_io.h>
#include <xft/types/io_types.h>

__attribute__((const, __always_inline__, __used__))
inline t_writer	xft_get_ts_fs_writer(t_buffer buffer, t_i32 fd,
	t_mutex *__restrict__ const mutex)
{
	static t_writer_vtable const	ts_fs = {
		.drain = xft_ts_stream_drain,
		.flush = xft_ts_stream_flush,
	};

	return ((t_writer)
		{
			.buffer = buffer,
			.end = 0,
			.vtable = &ts_fs,
			.as.ts_fs_writer.fd = fd,
			.as.ts_fs_writer.mutex = mutex,
		});
}

__attribute__((const, __always_inline__, __used__))
inline t_reader	xft_get_ts_fs_reader(t_buffer buffer, t_i32 fd,
	t_mutex *__restrict__ const mutex)
{
	static t_reader_vtable const	ts_fs = {
		.fill = xft_ts_stream_fill,
		.unbufered_fill = xft_ts_stream_unbuffered_fill,
	};

	return ((t_reader)
		{
			.buffer = buffer,
			.end = 0,
			.vtable = &ts_fs,
			.as.ts_fs_reader.fd = fd,
			.as.ts_fs_reader.mutex = mutex,
		});
}
