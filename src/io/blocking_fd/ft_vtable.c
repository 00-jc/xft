/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 11:58:04 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 14:03:14 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "private/ft_p_io.h"
#include "types/io_types.h"

__attribute__((const, __always_inline__))
inline t_writer	ft_get_fs_writer(t_buffer buffer, t_i32 fd)
{
	const static t_writer_vtable	fs = (t_writer_vtable)
	{
		.drain = ft_stream_drain,
		.flush = ft_stream_flush,
	};

	return ((t_writer)
		{
			.buffer = buffer,
			.end = 0,
			.vtable = &fs,
			.as.fs_writer.fd = fd,
		});
}

__attribute__((const, __always_inline__))
inline t_reader	ft_get_fs_reader(t_buffer buffer, t_i32 fd)
{
	const static t_reader_vtable	fs = (t_reader_vtable)
	{
		.fill = ft_stream_fill,
		.unbufered_fill = ft_stream_unbuffered_fill,
	};

	return ((t_reader)
		{
			.buffer = buffer,
			.end = 0,
			.vtable = &fs,
			.as.fs_reader.fd = fd,
		});
}
