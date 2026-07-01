/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writer_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 18:12:25 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "mem.h"
#include "types/io_types.h"

__attribute__((__always_inline__, __nonnull__(1)))
inline t_result	ft_writer_flush(t_writer *__restrict__ const writer)
{
	return (writer->vtable->flush(writer));
}

__attribute__((__always_inline__, __nonnull__(1)))
inline t_result	ft_writer_write(t_writer *__restrict__ const writer,
	t_buffer buf)
{
	t_size							head;
	t_iovec							vectorized[2];
	t_size							to_buffer;
	t_size							raw_written;

	if (writer->buffer.mem == nullptr || buf.mem == nullptr)
		__builtin_unreachable();
	head = writer->buffer.size - writer->end;
	if (buf.size <= head)
	{
		ft_memcpy(writer->buffer.mem + writer->end, buf.mem, buf.size);
		writer->end += buf.size;
		return (OK);
	}
	vectorized[0] = (t_iovec){writer->buffer.mem, writer->end};
	to_buffer = (buf.size + writer->end) % writer->buffer.size;
	raw_written = buf.size - to_buffer;
	vectorized[1] = (t_iovec){buf.mem, raw_written};
	if (__builtin_expect(
			writer->vtable->drain(writer, vectorized, 2) == KO, 0))
		return (KO);
	ft_memcpy(writer->buffer.mem, buf.mem + raw_written, to_buffer);
	writer->end = to_buffer;
	return (OK);
}
