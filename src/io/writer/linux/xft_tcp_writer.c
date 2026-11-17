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
		tmp = iov->size;
		ret = xft_sendto((int)ctx->socket, iov,
				(t_xft_msg_opts){.more = count > 1}, nullptr);
		n = iov->size;
		iov->size = tmp;
		if (__builtin_expect(ret != xft_sys_repeat && n == 0, 0))
			return (KO);
	}
}

__attribute__((__nonnull__(1)))
t_result	xft__tcp_writer_flush(t_writer *w)
{
	t_writer_ctx_tcp *const			ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->buf;
	t_size							done;
	t_iovec							iov;
	t_xft_sysres					ret;

	done = 0;
	while (done != buf.size)
	{
		iov = (t_iovec){.mem = buf.mem + done, .size = buf.size - done};
		ret = xft_sendto((int)ctx->socket, &iov, (t_xft_msg_opts){0}, nullptr);
		if (__builtin_expect(ret != xft_sys_repeat && iov.size == 0, 0))
			return (KO);
		done += iov.size;
	}
	ctx->buf.size = 0;
	return (OK);
}

__attribute__((__nonnull__(1, 4)))
static t_result	tcp_writer_copy_fd(t_writer *w, t_fd fd, t_size limit,
	t_size *size)
{
	t_writer_ctx_tcp *const	ctx = w->writer_ctx;
	const t_size			cap = ctx->buf.capacity;
	t_size					left;
	t_size					n;
	t_xft_sysres			ret;

	left = limit;
	n = 0;
	ret = xft_sys_repeat;
	while (left != 0 && (ret == xft_sys_repeat || n != 0))
	{
		ret = xft_read((int)fd, ctx->buf.mem, xft_tern_s(left < cap, left, cap),
				&n);
		if (__builtin_expect(ret == xft_sys_ko, 0))
			return (KO);
		ctx->buf.size = n;
		if (__builtin_expect(!xft__tcp_writer_flush(w), 0))
			return (KO);
		left -= n;
	}
	*size = limit - left;
	return (OK);
}

__attribute__((__nonnull__(1, 4)))
t_result	xft__tcp_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,
	t_size *size)
{
	t_writer_ctx_tcp *const	ctx = w->writer_ctx;
	const int				sock = (int)ctx->socket;
	t_size					left;
	t_size					n;
	t_xft_sysres			ret;

	if (__builtin_expect(!xft__tcp_writer_flush(w), 0))
		return (KO);
	left = limit;
	n = 0;
	ret = xft_sys_repeat;
	while (left != 0 && (ret == xft_sys_repeat || n != 0))
	{
		n = left;
		ret = xft_sendfile(sock, (int)fd, nullptr, &n);
		if (__builtin_expect(ret == xft_sys_ko && left != limit, 0))
			return (KO);
		if (ret == xft_sys_ko)
			return (tcp_writer_copy_fd(w, fd, limit, size));
		left -= n;
	}
	*size = limit - left;
	return (OK);
}

#endif
