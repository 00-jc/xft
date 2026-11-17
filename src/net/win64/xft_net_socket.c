/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_net_socket.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 01:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 01:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_net.h>

#if defined(_WIN32)

# include <xft/bmi.h>
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>
# include <ws2tcpip.h>

__attribute__((__nonnull__(3), __flatten__, __always_inline__, __used__))
inline t_result	xft_open_socket(t_ip_family family, t_socket_type type,
	t_fd *sock)
{
	const int	af = (int)xft_tern(family == xft_ipv4, AF_INET, AF_INET6);
	const int	kind = (int)xft_tern(type == xft_socket_tcp, SOCK_STREAM,
			SOCK_DGRAM);
	SOCKET		s;

	s = WSASocketW(af, kind, 0, nullptr, 0, WSA_FLAG_NO_HANDLE_INHERIT);
	*sock = (t_fd)s;
	return ((t_result)(s != INVALID_SOCKET));
}

__attribute__((__nonnull__(2), __flatten__))
t_result	xft_bind_socket(t_fd sock, const t_ip_addr *addr,
	t_ip_bind_opts opts)
{
	const SOCKET	s = (SOCKET)sock;
	SOCKADDR_IN6	sa;
	int				len;
	int				on;

	len = (int)xft__sockaddr_from_ip(addr, &sa);
	on = 1;
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char *)&on,
			sizeof(on)) != 0)
		return (KO);
	if (opts.allow_broadcast && setsockopt(s, SOL_SOCKET, SO_BROADCAST,
			(const char *)&on, sizeof(on)) != 0)
		return (KO);
	on = opts.ipv6_only;
	if (sa.sin6_family == AF_INET6 && setsockopt(s, IPPROTO_IPV6,
			IPV6_V6ONLY, (const char *)&on, sizeof(on)) != 0)
		return (KO);
	return ((t_result)(bind(s, (SOCKADDR *)&sa, len) == 0));
}

__attribute__((__flatten__, __always_inline__, __used__))
inline t_result	xft_listen_socket(t_fd sock, t_u32a backlog)
{
	return ((t_result)(listen((SOCKET)sock, (int)xft_tern(backlog == 0,
				SOMAXCONN, backlog)) == 0));
}

__attribute__((__flatten__, __always_inline__, __used__))
inline t_result	xft_close_socket(t_fd sock)
{
	return ((t_result)(closesocket((SOCKET)sock) == 0));
}

#endif
