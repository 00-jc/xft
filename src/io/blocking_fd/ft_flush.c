/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 12:33:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 13:36:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_io.h"
#include "types/io_types.h"

__attribute__((__nonnull__(1), __always_inline__))
inline t_result	ft_stream_flush(void *__restrict__ const writer)
{
	t_writer *__restrict__ const	w = writer;
	t_size							bytes_written;
	t_ssize							res;

	if (w->buffer.mem == nullptr)
		__builtin_unreachable();
	bytes_written = 0;
	while (bytes_written != w->end)
	{
		res = ft_write(w->as.fs_writer.fd, w->buffer.mem + bytes_written,
				w->end - bytes_written);
		if (__builtin_expect(res <= 0, 0))
			return (KO);
		bytes_written += (t_size)res;
	}
	w->end = 0;
	return (OK);
}
