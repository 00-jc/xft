/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 13:45:26 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 14:06:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_io.h"

__attribute__((__always_inline__, __nonnull__(1, 2, 4), __used__))
inline t_result	xft_stream_unbuffered_fill(t_any __restrict__ const ptr,
	t_u8 *__restrict__ const dst, const t_size len,
	t_size *__restrict__ const total)
{
	t_reader *__restrict__ const	reader = ptr;
	t_ssize							ret;
	t_size							remain;
	t_size							bytes_read;

	if (reader->buffer.mem == nullptr)
		__builtin_unreachable();
	remain = reader->valid - reader->end;
	xft_memcpy(dst, reader->buffer.mem + reader->end, remain);
	reader->end = 0;
	reader->valid = 0;
	bytes_read = remain;
	while (len != bytes_read)
	{
		ret = xft_read(reader->as.fs_reader.fd,
				dst + bytes_read, len - bytes_read);
		if (__builtin_expect(ret < 0, 0))
			return (KO);
		if (__builtin_expect(ret == 0, 0))
			break ;
		bytes_read += ret;
	}
	*total = bytes_read;
	return (OK);
}

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_result	xft_stream_fill(t_any __restrict__ const reader)
{
	t_reader *__restrict const	rd = reader;
	t_ssize						ret;

	if (rd->buffer.mem == nullptr)
		__builtin_unreachable();
	ret = xft_read(rd->as.fs_reader.fd, rd->buffer.mem, rd->buffer.size);
	if (ret < 0)
		return (KO);
	rd->valid = ret;
	rd->end = 0;
	return (OK);
}
