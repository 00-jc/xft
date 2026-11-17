/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_tcp_v6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_tcp_v6(void)
{
	const t_ip_addr			lo = {.family = xft_ipv6,
		.v6 = {.address = {{[15] = 1}}, .port = 47203}};
	const t_ip_bind_opts	only6 = {.ipv6_only = 1};
	t_fd					fds[3];
	t_ip_addr				peer;

	if (!xft_open_socket(xft_ipv6, xft_socket_tcp, &fds[0]))
		return ;
	if (!xft_bind_socket(fds[0], &lo, only6))
	{
		net_check(xft_close_socket(fds[0]), "close unbindable v6 socket");
		return ;
	}
	net_check(xft_listen_socket(fds[0], 0), "xft_listen_socket v6");
	net_check(xft_open_socket(xft_ipv6, xft_socket_tcp, &fds[1])
		&& xft_connect_socket(fds[1], &lo, (t_connect_options){
			.has_timeout = true, .timeout_ms = 1000}), "connect v6 timeout");
	net_check(xft_accept_socket(fds[0], &peer, &fds[2])
		&& peer.family == xft_ipv6 && peer.v6.address.bytes[15] == 1,
		"accept v6 peer is ::1");
	net_check(xft_close_socket(fds[2]) && xft_close_socket(fds[1])
		&& xft_close_socket(fds[0]), "close v6 sockets");
}
