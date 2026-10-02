/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_vtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 11:58:04 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/04 00:23:44 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "xft_p_io.h"
#include "types/io_types.h"

__attribute__((const, __always_inline__, __used__))
inline t_writer	xft_get_fs_writer(t_buffer buffer, t_i32 fd)
{
	static t_writer_vtable const	fs = {
		.drain = xft_stream_drain,
		.flush = xft_stream_flush,
	};

	return ((t_writer)
		{
			.buffer = buffer,
			.end = 0,
			.vtable = &fs,
			.as.fs_writer.fd = fd,
		});
}

__attribute__((const, __always_inline__, __used__))
inline t_reader	xft_get_fs_reader(t_buffer buffer, t_i32 fd)
{
	static t_reader_vtable const	fs = {
		.fill = xft_stream_fill,
		.unbufered_fill = xft_stream_unbuffered_fill,
	};

	return ((t_reader)
		{
			.buffer = buffer,
			.end = 0,
			.vtable = &fs,
			.as.fs_reader.fd = fd,
		});
}
