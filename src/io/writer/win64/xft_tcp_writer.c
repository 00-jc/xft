/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tcp_writer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 18:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 18:40:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>

#if defined(_WIN32)

# include <xft/bmi.h>
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>

__attribute__((__nonnull__(1, 2)))
t_result	xft__tcp_writer_writev(t_writer_ctx_tcp *ctx, t_iovec *iov,
	t_size count)
{
	const SOCKET	sock = (SOCKET)ctx->socket;
	t_size			len;
	int				n;
	bool			done;

	while (count != 0)
	{
		len = iov->size;
		len = xft_tern_s(len < MAXLONG, len, MAXLONG);
		n = send(sock, (const char *)iov->mem, (int)len, 0);
		if (__builtin_expect(n < 0 || (n == 0 && len != 0), 0))
			return ((t_result){.ok = KO, .err = xft_err_none});
		iov->mem += n;
		iov->size -= (t_size)n;
		done = iov->size == 0;
		iov += done;
		count -= done;
	}
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1)))
t_result	xft__tcp_writer_flush(t_writer *w)
{
	t_writer_ctx_tcp *const			ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->buf;
	t_size							done;
	t_size							len;
	int								n;

	done = 0;
	while (done != buf.size)
	{
		len = buf.size - done;
		len = xft_tern_s(len < MAXLONG, len, MAXLONG);
		n = send((SOCKET)ctx->socket, (const char *)buf.mem + done,
				(int)len, 0);
		if (__builtin_expect(n <= 0, 0))
			return ((t_result){.ok = KO, .err = xft_err_none});
		done += (t_size)n;
	}
	ctx->buf.size = 0;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1, 4), __always_inline__))
static inline t_result	xft__tcp_writer_refill(t_writer *w, t_fd fd,
	t_size want, DWORD *n)
{
	t_writer_ctx_tcp *const	ctx = w->writer_ctx;
	t_result				ret;
	BOOL					ok;

	ret = xft__tcp_writer_flush(w);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	ok = ReadFile((HANDLE)fd, ctx->buf.mem, (DWORD)want, n, nullptr);
	return ((t_result){.ok = ok || GetLastError() == ERROR_BROKEN_PIPE});
}

__attribute__((__nonnull__(1, 4)))
t_result	xft__tcp_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,
	t_size *size)
{
	t_writer_ctx_tcp *const	ctx = w->writer_ctx;
	t_size					cap;
	t_size					left;
	DWORD					n;
	t_result				ret;

	cap = ctx->buf.capacity;
	cap = xft_tern_s(cap < MAXDWORD, cap, MAXDWORD);
	left = limit;
	n = 1;
	while (left != 0 && n != 0)
	{
		ret = xft__tcp_writer_refill(w, fd,
				xft_tern_s(left < cap, left, cap), &n);
		if (__builtin_expect(!ret.ok, 0))
			return (ret);
		ctx->buf.size = n;
		left -= n;
	}
	*size = limit - left;
	return ((t_result){.ok = OK});
}

#endif
