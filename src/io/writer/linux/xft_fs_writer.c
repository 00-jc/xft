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

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1, 2)))
t_result	xft__fs_writer_writev(t_writer_fs *ctx, t_iovec *iov, t_size count)
{
	t_size			n;
	t_xft_sysres	ret;

	n = 0;
	while (true)
	{
		while (count != 0 && n >= iov->size)
		{
			n -= iov->size;
			++iov;
			--count;
		}
		if (count == 0)
			return (OK);
		iov->mem += n;
		iov->size -= n;
		ret = xft_writev((int)ctx->fd, iov, count, &n);
		if (__builtin_expect(ret != xft_sys_repeat && n == 0, 0))
			return (KO);
	}
}

__attribute__((__nonnull__(1)))
t_result	xft__fs_writer_flush(t_writer *w)
{
	t_writer_fs *const	ctx = w->writer_ctx;
	t_size				done;
	t_size				len;
	t_size				n;
	t_xft_sysres		ret;

	if (ctx->buffer.mem == nullptr)
		__builtin_unreachable();
	done = 0;
	while (done != ctx->buffer.size)
	{
		len = ctx->buffer.size - done;
		ret = xft_write((int)ctx->fd, ctx->buffer.mem + done, len, &n);
		if (__builtin_expect(ret != xft_sys_repeat && n == 0, 0))
			return (KO);
		done += n;
	}
	ctx->buffer.size = 0;
	return (OK);
}

#endif
