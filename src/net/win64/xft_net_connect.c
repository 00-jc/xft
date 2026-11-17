/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_net_connect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 01:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 01:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_net.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>
# include <ws2tcpip.h>

__attribute__((__nonnull__(2)))
static bool	connect_timeout(SOCKET s, const SOCKADDR *sa, int len,
	t_u64a ms)
{
	u_long	mode;
	fd_set	wr;
	fd_set	ex;
	TIMEVAL	tv;

	mode = 1;
	if (ioctlsocket(s, FIONBIO, &mode) != 0)
		return (false);
	if (connect(s, sa, len) != 0 && WSAGetLastError() != WSAEWOULDBLOCK)
		return (false);
	wr = (fd_set){.fd_count = 1, .fd_array = {s}};
	ex = wr;
	tv = (TIMEVAL){.tv_sec = (long)(ms / 1000),
		.tv_usec = (long)(ms % 1000 * 1000)};
	if (select(0, nullptr, &wr, &ex, &tv) != 1 || wr.fd_count != 1)
		return (false);
	mode = 0;
	return (ioctlsocket(s, FIONBIO, &mode) == 0);
}

__attribute__((__nonnull__(2), __flatten__))
t_result	xft_connect_socket(t_fd sock, const t_ip_addr *addr,
	t_connect_options opts)
{
	const SOCKET	s = (SOCKET)sock;
	SOCKADDR_IN6	sa;
	int				len;

	len = (int)xft__sockaddr_from_ip(addr, &sa);
	if (opts.has_timeout)
		return ((t_result)connect_timeout(s, (SOCKADDR *)&sa, len,
				opts.timeout_ms));
	return ((t_result)(connect(s, (SOCKADDR *)&sa, len) == 0));
}

__attribute__((__nonnull__(3), __flatten__))
t_result	xft_accept_socket(t_fd server, t_ip_addr *peer, t_fd *conn)
{
	SOCKADDR_IN6	sa;
	SOCKET			s;
	int				len;

	len = sizeof(sa);
	s = accept((SOCKET)server, (SOCKADDR *)&sa, &len);
	if (__builtin_expect(s == INVALID_SOCKET, 0))
		return (KO);
	if (peer != nullptr)
		xft__ip_from_sockaddr(&sa, peer);
	*conn = (t_fd)s;
	return (OK);
}

#endif
