/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 23:50:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 00:03:39 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "private/ft_p_io.h"
#include "types/io_types.h"

__attribute__((const, __always_inline__))
inline t_writer	ft_get_raw_writer(t_buffer buffer,
	t_u8 *__restrict__ const external, t_size external_valid)
{
	const static t_writer_vtable	raw = (t_writer_vtable)
	{
		.drain = ft_raw_drain,
		.flush = ft_raw_flush,
	};

	return ((t_writer)
		{
			.buffer = buffer,
			.end = 0,
			.vtable = &raw,
			.as.mem_writer.external = external,
			.as.mem_writer.external_valid = external_valid,
			.as.mem_writer.external_size = 0,
		});
}

__attribute__((const, __always_inline__))
inline t_reader	ft_get_raw_reader(t_buffer buffer, t_buffer external)
{
	const static t_reader_vtable	raw = (t_reader_vtable)
	{
		.fill = ft_stream_fill,
		.unbufered_fill = ft_stream_unbuffered_fill,
	};

	return ((t_reader)
		{
			.buffer = buffer,
			.end = 0,
			.vtable = &raw,
			.as.mem_reader.external = external,
			.as.mem_reader.drained = 0,
		});
}
