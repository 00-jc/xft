/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_sockets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

t_fd	net_listen(const t_ip_addr *addr)
{
	t_fd	fd;

	net_check(xft_open_socket(addr->family, xft_socket_tcp, &fd).ok,
		"xft_open_socket listener");
	net_check(xft_bind_socket(fd, addr, (t_ip_bind_opts){0}).ok
		&& xft_listen_socket(fd, 0).ok, "xft_bind_socket + xft_listen_socket");
	return (fd);
}

t_fd	net_connect(const t_ip_addr *addr)
{
	t_fd	fd;

	net_check(xft_open_socket(addr->family, xft_socket_tcp, &fd).ok,
		"xft_open_socket client");
	net_check(xft_connect_socket(fd, addr, (t_connect_options){0}).ok,
		"xft_connect_socket");
	return (fd);
}

t_fd	net_udp(const t_ip_addr *addr)
{
	t_fd	fd;

	net_check(xft_open_socket(addr->family, xft_socket_udp, &fd).ok,
		"xft_open_socket udp");
	net_check(xft_bind_socket(fd, addr, (t_ip_bind_opts){0}).ok,
		"xft_bind_socket udp");
	return (fd);
}
