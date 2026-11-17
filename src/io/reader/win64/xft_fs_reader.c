/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fs_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>

#if defined(_WIN32)

# include <xft/bmi.h>
# include <xft/mem.h>
# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__nonnull__(1, 2, 4)))
t_result	xft__fs_reader_stream(t_reader *r, t_writer *w, t_size limit,
	t_size *size)
{
	t_reader_fs *const	ctx = r->reader_ctx;
	t_size				len;
	DWORD				n;
	BOOL				ok;
	t_buffer			chunk;

	if (ctx->buffer.mem == nullptr || w->vtable.drain_all == nullptr)
		__builtin_unreachable();
	*size = 0;
	n = 1;
	while (*size != limit && n != 0)
	{
		len = xft_tern_s(limit - *size < ctx->buffer.size, limit - *size,
				ctx->buffer.size);
		len = xft_tern_s(len < MAXDWORD, len, MAXDWORD);
		ok = ReadFile((HANDLE)ctx->fd, ctx->buffer.mem, (DWORD)len, &n,
				nullptr);
		if (__builtin_expect(!ok && GetLastError() != ERROR_BROKEN_PIPE, 0))
			return (KO);
		chunk = xft_fatptr(ctx->buffer.mem, n);
		if (__builtin_expect(!w->vtable.drain_all(w, chunk), 0))
			return (KO);
		*size += n;
	}
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
t_result	xft__fs_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	t_reader_fs *const	ctx = r->reader_ctx;
	t_size				len;
	DWORD				n;
	BOOL				ok;

	if (ctx->buffer.mem == nullptr)
		__builtin_unreachable();
	*size = 0;
	n = 1;
	while (*size != limit && n != 0)
	{
		len = xft_tern_s(limit - *size < ctx->buffer.size, limit - *size,
				ctx->buffer.size);
		len = xft_tern_s(len < MAXDWORD, len, MAXDWORD);
		ok = ReadFile((HANDLE)ctx->fd, ctx->buffer.mem, (DWORD)len, &n,
				nullptr);
		if (__builtin_expect(!ok && GetLastError() != ERROR_BROKEN_PIPE, 0))
			return (KO);
		*size += n;
	}
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
t_result	xft__fs_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	t_reader_fs *const	ctx = r->reader_ctx;
	t_size				len;
	DWORD				n;
	BOOL				ok;

	if (dst.mem == nullptr)
		__builtin_unreachable();
	*size = 0;
	n = 1;
	while (*size != dst.size && n != 0)
	{
		len = dst.size - *size;
		len = xft_tern_s(len < MAXDWORD, len, MAXDWORD);
		ok = ReadFile((HANDLE)ctx->fd, dst.mem + *size, (DWORD)len, &n,
				nullptr);
		if (__builtin_expect(!ok && GetLastError() != ERROR_BROKEN_PIPE, 0))
			return (KO);
		*size += n;
	}
	return (OK);
}

#endif
