/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 13:45:26 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 13:17:11 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_io.h"

__attribute__((__always_inline__, __nonnull__(1, 2, 4)))
inline t_result	ft__stream_unbuffered(t_reader *__restrict__ const reader,
		t_u8 *__restrict__ const dst, t_size len,
		t_size *__restrict__ const total)
{
	t_size	available;

	available = reader->as.mem_reader.external.size
		- reader->as.mem_reader.drained;
	available = ft_tern(available < len, available, len);
	ft_memcpy(dst, reader->as.mem_reader.external.mem
		+ reader->as.mem_reader.drained, available);
	reader->as.mem_reader.drained += available;
	*total = available;
	return (OK);
}

__attribute__((__always_inline__, __nonnull__(1, 2, 4)))
inline t_result	ft_stream_unbuffered_fill(void *__restrict__ const ptr,
	t_u8 *__restrict__ const dst, const t_size len,
	t_size *__restrict__ const total)
{
	t_reader *__restrict__ const	reader = ptr;
	t_size							remain;
	t_size							bytes_read;
	t_size							to_copy;

	if (reader->buffer.mem == nullptr
		|| reader->as.mem_reader.external.mem == nullptr)
		__builtin_unreachable();
	remain = reader->valid - reader->end;
	to_copy = ft_tern(remain < len, remain, len);
	ft_memcpy(dst, reader->buffer.mem + reader->end, to_copy);
	reader->end = ft_tern(to_copy == remain, 0, reader->end + to_copy);
	reader->valid = ft_tern(to_copy == remain, 0, reader->valid);
	bytes_read = to_copy;
	if (bytes_read < len)
	{
		if (__builtin_expect(ft__stream_unbuffered(reader, dst + bytes_read,
					len - bytes_read, total) == KO, 0))
			return (KO);
		*total += bytes_read;
		return (OK);
	}
	*total = bytes_read;
	return (OK);
}

__attribute__((__always_inline__, __nonnull__(1)))
inline t_result	ft_stream_fill(void *__restrict__ const reader)
{
	t_reader *__restrict const	rd = reader;
	t_buffer					external;
	t_size						max_read;

	external = rd->as.mem_reader.external;
	max_read = external.size - rd->as.mem_reader.drained;
	max_read = ft_tern(rd->buffer.size < max_read, rd->buffer.size, max_read);
	ft_memcpy(rd->buffer.mem, external.mem + rd->as.mem_reader.drained,
		max_read);
	rd->as.mem_reader.drained += max_read;
	rd->valid = max_read;
	rd->end = 0;
	return (OK);
}
