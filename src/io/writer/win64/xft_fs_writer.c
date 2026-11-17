/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fs_writer.c                                    :+:      :+:    :+:   */
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
# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__nonnull__(1, 2)))
t_result	xft__fs_writer_writev(t_writer_fs *ctx, t_iovec *iov, t_size count)
{
	t_size	len;
	DWORD	n;
	BOOL	ok;
	bool	done;

	while (count != 0)
	{
		len = xft_tern_s(iov->size < MAXDWORD, iov->size, MAXDWORD);
		ok = WriteFile((HANDLE)ctx->fd, iov->mem, (DWORD)len, &n, nullptr);
		if (__builtin_expect(!ok || (n == 0 && len != 0), 0))
			return (KO);
		iov->mem += n;
		iov->size -= n;
		done = iov->size == 0;
		iov += done;
		count -= done;
	}
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	xft__fs_writer_flush(t_writer *w)
{
	t_writer_fs *const	ctx = w->writer_ctx;
	t_size				done;
	t_size				len;
	DWORD				n;
	BOOL				ok;

	if (ctx->buffer.mem == nullptr)
		__builtin_unreachable();
	done = 0;
	while (done != ctx->buffer.size)
	{
		len = ctx->buffer.size - done;
		len = xft_tern_s(len < MAXDWORD, len, MAXDWORD);
		ok = WriteFile((HANDLE)ctx->fd, ctx->buffer.mem + done, (DWORD)len,
				&n, nullptr);
		if (__builtin_expect(!ok || n == 0, 0))
			return (KO);
		done += n;
	}
	ctx->buffer.size = 0;
	return (OK);
}

#endif
