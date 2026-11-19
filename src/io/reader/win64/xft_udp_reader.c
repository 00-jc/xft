/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_udp_reader.c                                   :+:      :+:    :+:   */
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
# include <xft/mem.h>
# include <xft/xft_p_net.h>
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>
# include <ws2tcpip.h>

__attribute__((__nonnull__(1, 3)))
t_result	xft__udp_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	t_reader_ctx_udp *const	ctx = r->reader_ctx;
	SOCKADDR_IN6			sa;
	int						cap;
	int						len;
	int						n;

	if (dst.mem == nullptr)
		__builtin_unreachable();
	cap = (int)xft_tern_s(dst.size < MAXLONG, dst.size, MAXLONG);
	len = sizeof(sa);
	n = recvfrom((SOCKET)ctx->socket, (char *)dst.mem, cap, 0,
			(SOCKADDR *)&sa, &len);
	if (__builtin_expect(n < 0 && WSAGetLastError() != WSAEMSGSIZE, 0))
		return ((t_result){.ok = KO, .err = xft_err_none});
	xft__ip_from_sockaddr(&sa, &ctx->ip);
	*size = xft_tern_s(n < 0, (t_size)cap, (t_size)n);
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1, 3)))
t_result	xft__udp_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	t_reader_ctx_udp *const	ctx = r->reader_ctx;
	const t_buffer			buf = ctx->buf;

	return (xft__udp_reader_read(r,
			xft_fatptr(buf.mem, xft_tern_s(limit < buf.size, limit, buf.size)),
			size));
}

#endif
