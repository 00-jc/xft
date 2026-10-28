/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_flush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 12:33:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 13:36:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/types/io_types.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __nonnull__(2)))
static inline t_ssize	xft__write(t_i32 fd, const t_u8 *__restrict__ buf,
	t_size len)
{
	DWORD	n;

	if (!WriteFile((HANDLE)(intptr_t)fd, buf,
		(DWORD)xft_tern(len < 0xFFFFFFFF, len, 0xFFFFFFFF), &n, nullptr))
		return (-1);
	return ((t_ssize)n);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_result	xft_stream_flush(t_any __restrict__ const writer)
{
	t_writer *__restrict__ const	w = writer;
	t_size							bytes_written;
	t_ssize							res;

	if (w->buffer.mem == nullptr)
		__builtin_unreachable();
	bytes_written = 0;
	while (bytes_written != w->end)
	{
		res = xft__write(w->as.fs_writer.fd, w->buffer.mem + bytes_written,
				w->end - bytes_written);
		if (__builtin_expect(res <= 0, 0))
			return (KO);
		bytes_written += (t_size)res;
	}
	w->end = 0;
	return (OK);
}

#endif
