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

# include <xft/bmi.h>
# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1, 2)))
t_result	xft__fs_writer_writev(t_writer_fs *ctx, t_iovec *iov, t_size count)
{
	t_size			n;
	t_result		ret;

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
			return ((t_result){.ok = OK});
		iov->mem += n;
		iov->size -= n;
		ret = xft_writev((int)ctx->fd, iov, count, &n);
		if (__builtin_expect(!xft_should_retry(ret) && n == 0, 0))
			return ((t_result){.ok = KO, .err = ret.err});
	}
}

__attribute__((__nonnull__(1)))
t_result	xft__fs_writer_flush(t_writer *w)
{
	t_writer_fs *const				ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->buffer;
	t_size							done;
	t_size							n;
	t_result						ret;

	if (buf.mem == nullptr)
		__builtin_unreachable();
	done = 0;
	while (done != buf.size)
	{
		ret = xft_write((int)ctx->fd, buf.mem + done, buf.size - done, &n);
		if (__builtin_expect(!xft_should_retry(ret) && n == 0, 0))
			return ((t_result){.ok = KO, .err = ret.err});
		done += n;
	}
	ctx->buffer.size = 0;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1, 4), __always_inline__))
static inline t_result	xft__fs_writer_refill(t_writer *w, t_fd fd, t_size want,
	t_size *n)
{
	t_writer_fs *const	ctx = w->writer_ctx;
	t_result			ret;

	ret = xft__fs_writer_flush(w);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	return (xft_read((int)fd, ctx->buffer.mem, want, n));
}

__attribute__((__nonnull__(1, 4)))
t_result	xft__fs_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,
	t_size *size)
{
	t_writer_fs *const	ctx = w->writer_ctx;
	const t_size		cap = ctx->buffer.capacity;
	t_size				left;
	t_size				n;
	t_result			ret;

	left = limit;
	n = 0;
	ret = (t_result){.err = xft_err_retry};
	while (left != 0 && (xft_should_retry(ret) || n != 0))
	{
		ret = xft__fs_writer_refill(w, fd,
				xft_tern_s(left < cap, left, cap), &n);
		if (__builtin_expect(!ret.ok && !xft_should_retry(ret), 0))
			return (ret);
		ctx->buffer.size = n;
		left -= n;
	}
	*size = limit - left;
	return ((t_result){.ok = OK});
}

#endif
