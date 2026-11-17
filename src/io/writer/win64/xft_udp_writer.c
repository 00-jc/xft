/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_udp_writer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 22:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 22:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>

#if defined(_WIN32)

# include <xft/bmi.h>
# include <xft/xft_p_net.h>
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>
# include <ws2tcpip.h>

__attribute__((__nonnull__(1)))
t_result	xft__udp_writer_send(t_writer_ctx_udp *ctx, t_buffer data)
{
	const SOCKET	s = (SOCKET)ctx->socket;
	SOCKADDR_IN6	sa;
	int				len;
	int				n;

	len = (int)xft__sockaddr_from_ip(&ctx->ip, &sa);
	n = sendto(s, (const char *)data.mem, (int)data.size, 0,
			(SOCKADDR *)&sa, len);
	return ((t_result)(n >= 0 && (t_size)n == data.size));
}

__attribute__((__nonnull__(1, 4)))
t_result	xft__udp_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,
	t_size *size)
{
	t_writer_ctx_udp *const	ctx = w->writer_ctx;
	t_size					cap;
	t_size					left;
	DWORD					n;
	BOOL					ok;

	cap = ctx->buf.capacity;
	cap = xft_tern_s(cap < MAXDWORD, cap, MAXDWORD);
	left = limit;
	n = 1;
	while (left != 0 && n != 0)
	{
		if (__builtin_expect(!xft__udp_writer_flush(w), 0))
			return (KO);
		ok = ReadFile((HANDLE)fd, ctx->buf.mem,
				(DWORD)xft_tern_s(left < cap, left, cap), &n, nullptr);
		if (__builtin_expect(!ok && GetLastError() != ERROR_BROKEN_PIPE, 0))
			return (KO);
		ctx->buf.size = n;
		left -= n;
	}
	*size = limit - left;
	return (OK);
}

#endif
