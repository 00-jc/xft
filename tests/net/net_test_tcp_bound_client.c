/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_tcp_bound_client.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_tcp_bound_client(void)
{
	const t_ip_addr	lo = net_lo4(47220);
	const t_ip_addr	local = net_lo4(47221);
	const t_fd		srv = net_listen(&lo);
	t_fd			fds[2];
	t_ip_addr		peer;

	net_check(xft_open_socket(xft_ipv4, xft_socket_tcp, &fds[0]).ok,
		"xft_open_socket client");
	net_check(xft_bind_socket(fds[0], &local, (t_ip_bind_opts){0}).ok,
		"bind client before connect");
	net_check(xft_connect_socket(fds[0], &lo, (t_connect_options){0}).ok,
		"connect bound client");
	net_check(xft_accept_socket(srv, &peer, &fds[1]).ok
		&& peer.v4.port == 47221, "server sees the client's bound port");
	net_check(xft_close_socket(fds[1]).ok && xft_close_socket(fds[0]).ok
		&& xft_close_socket(srv).ok, "close bound client sockets");
}
