/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tcp_writer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 17:56:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 18:24:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>

#if defined(__linux__)

# include <xft/bmi.h>
# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1, 2)))
t_result	xft__tcp_writer_writev(t_writer_ctx_tcp *ctx, t_iovec *iov,
	t_size count)
{
	t_size			n;
	t_size			tmp;
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
		tmp = iov->size;
		ret = xft_sendto((int)ctx->socket, iov,
				(t_xft_msg_opts){.more = count > 1}, nullptr);
		n = iov->size;
		iov->size = tmp;
		if (__builtin_expect(!xft_should_retry(ret) && n == 0, 0))
			return ((t_result){.ok = KO, .err = ret.err});
	}
}

__attribute__((__nonnull__(1)))
t_result	xft__tcp_writer_flush(t_writer *w)
{
	t_writer_ctx_tcp *const			ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->buf;
	t_size							done;
	t_iovec							iov;
	t_result						ret;

	done = 0;
	while (done != buf.size)
	{
		iov = (t_iovec){.mem = buf.mem + done, .size = buf.size - done};
		ret = xft_sendto((int)ctx->socket, &iov, (t_xft_msg_opts){0}, nullptr);
		if (__builtin_expect(!xft_should_retry(ret) && iov.size == 0, 0))
			return ((t_result){.ok = KO, .err = ret.err});
		done += iov.size;
	}
	ctx->buf.size = 0;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1, 4), __always_inline__))
static inline t_result	xft__tcp_writer_copy_step(t_writer *w, t_fd fd,
	t_size want, t_size *n)
{
	t_writer_ctx_tcp *const	ctx = w->writer_ctx;
	t_result				ret;
	t_result				flushed;

	ret = xft_read((int)fd, ctx->buf.mem, want, n);
	if (__builtin_expect(!ret.ok && !xft_should_retry(ret), 0))
		return (ret);
	ctx->buf.size = *n;
	flushed = xft__tcp_writer_flush(w);
	if (__builtin_expect(!flushed.ok, 0))
		return (flushed);
	return (ret);
}

__attribute__((__nonnull__(1, 4)))
static t_result	xft__tcp_writer_copy_fd(t_writer *w, t_fd fd, t_size limit,
	t_size *size)
{
	t_writer_ctx_tcp *const	ctx = w->writer_ctx;
	const t_size			cap = ctx->buf.capacity;
	t_size					left;
	t_size					n;
	t_result				ret;

	left = limit;
	n = 0;
	ret = (t_result){.err = xft_err_retry};
	while (left != 0 && (xft_should_retry(ret) || n != 0))
	{
		ret = xft__tcp_writer_copy_step(w, fd,
				xft_tern_s(left < cap, left, cap), &n);
		if (__builtin_expect(!ret.ok && !xft_should_retry(ret), 0))
			return (ret);
		left -= n;
	}
	*size = limit - left;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1, 4)))
t_result	xft__tcp_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,
	t_size *size)
{
	t_writer_ctx_tcp *const	ctx = w->writer_ctx;
	const int				sock = (int)ctx->socket;
	t_size					left;
	t_size					n;
	t_result				ret;

	ret = xft__tcp_writer_flush(w);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	left = limit;
	n = 0;
	ret = (t_result){.err = xft_err_retry};
	while (left != 0 && (xft_should_retry(ret) || n != 0))
	{
		n = left;
		ret = xft_sendfile(sock, (int)fd, nullptr, &n);
		if (__builtin_expect(!ret.ok && !xft_should_retry(ret)
				&& left != limit, 0))
			return (ret);
		if (!ret.ok && !xft_should_retry(ret))
			return (xft__tcp_writer_copy_fd(w, fd, limit, size));
		left -= n;
	}
	*size = limit - left;
	return ((t_result){.ok = OK});
}

#endif
