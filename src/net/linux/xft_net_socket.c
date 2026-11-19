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

#if defined(__linux__)

# include <xft/bmi.h>
# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(3), __flatten__, __always_inline__, __used__))
inline t_result	xft_open_socket(t_ip_family family, t_socket_type type,
	t_fd *sock)
{
	const int		af = (int)xft_tern(family == xft_ipv4, xft_af_inet,
			xft_af_inet6);
	const int		kind = (int)xft_tern(type == xft_socket_tcp,
			xft_sock_stream, xft_sock_dgram);
	int				s;
	t_result		ret;

	s = -1;
	ret = (t_result){.err = xft_err_retry};
	while (xft_should_retry(ret))
		ret = xft_socket(af, kind | xft_sock_cloexec, 0, &s);
	*sock = (t_fd)s;
	return (ret);
}

__attribute__((__always_inline__))
static inline t_result	xft__set_bind_opts(int fd, t_ip_bind_opts opts,
	t_u16a family)
{
	int				on;
	const t_iovec	val = {.mem = (t_u8 *)&on, .size = sizeof(on)};
	t_result		ret;

	on = 1;
	ret = xft_setsockopt(fd, xft_sol_socket, xft_so_reuseaddr, val);
	if (!ret.ok)
		return (ret);
	if (opts.allow_broadcast)
		ret = xft_setsockopt(fd, xft_sol_socket, xft_so_broadcast, val);
	if (!ret.ok)
		return (ret);
	on = opts.ipv6_only;
	if (family == xft_af_inet6)
		ret = xft_setsockopt(fd, xft_ipproto_ipv6, xft_ipv6_v6only, val);
	return (ret);
}

__attribute__((__nonnull__(2), __flatten__))
t_result	xft_bind_socket(t_fd sock, const t_ip_addr *addr,
	t_ip_bind_opts opts)
{
	const int		fd = (int)sock;
	t_sockaddr_in6	sa;
	t_u32a			len;
	t_result		ret;

	len = xft__sockaddr_from_ip(addr, &sa);
	ret = xft__set_bind_opts(fd, opts, sa.sin6_family);
	if (!ret.ok)
		return (ret);
	return (xft_bind(fd, (t_sockaddr *)&sa, len));
}

__attribute__((__flatten__, __always_inline__, __used__))
inline t_result	xft_listen_socket(t_fd sock, t_u32a backlog)
{
	return (xft_listen((int)sock, (int)xft_tern(backlog == 0, xft_somaxconn,
				backlog)));
}

__attribute__((__flatten__, __always_inline__, __used__))
inline t_result	xft_close_socket(t_fd sock)
{
	return (xft_close((int)sock));
}

#endif
