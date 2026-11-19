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

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(2), __flatten__))
t_result	xft_connect_socket(t_fd sock, const t_ip_addr *addr,
	t_connect_options opts)
{
	const int		fd = (int)sock;
	t_sock_timeval	tv;
	const t_iovec	val = {.mem = (t_u8 *)&tv, .size = sizeof(tv)};
	t_sockaddr_in6	sa;
	t_u32a			len;

	len = xft__sockaddr_from_ip(addr, &sa);
	if (!opts.has_timeout)
		return (xft_connect(fd, (t_sockaddr *)&sa, len));
	tv = (t_sock_timeval){.tv_sec = (t_i64a)(opts.timeout_ms / 1000),
		.tv_usec = (t_i64a)(opts.timeout_ms % 1000 * 1000)};
	if (!xft_setsockopt(fd, xft_sol_socket, xft_so_sndtimeo_new, val).ok)
		return ((t_result){.ok = KO});
	if (!xft_connect(fd, (t_sockaddr *)&sa, len).ok)
		return ((t_result){.ok = KO});
	tv = (t_sock_timeval){0};
	return (xft_setsockopt(fd, xft_sol_socket, xft_so_sndtimeo_new, val));
}

__attribute__((__nonnull__(3), __flatten__))
t_result	xft_accept_socket(t_fd server, t_ip_addr *peer, t_fd *conn)
{
	t_sockaddr_in6	sa;
	int				fd;
	t_result		ret;

	fd = -1;
	ret = (t_result){.err = xft_err_retry};
	while (xft_should_retry(ret))
		ret = xft_accept((int)server, xft_sock_cloexec, &sa, &fd);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	if (peer != nullptr)
		xft__ip_from_sockaddr(&sa, peer);
	*conn = (t_fd)fd;
	return ((t_result){.ok = OK});
}

#endif
