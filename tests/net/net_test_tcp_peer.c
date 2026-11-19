/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_tcp_peer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_tcp_peer(void)
{
	const t_ip_addr	lo = net_lo4(47202);
	const t_fd		srv = net_listen(&lo);
	const t_fd		cli = net_connect(&lo);
	t_fd			conn;
	t_ip_addr		peer;

	net_check(xft_accept_socket(srv, &peer, &conn).ok,
		"xft_accept_socket peer");
	net_check(peer.family == xft_ipv4 && peer.v4.address.bytes[0] == 127
		&& peer.v4.address.bytes[3] == 1, "accept peer is 127.0.0.1");
	net_check(xft_close_socket(conn).ok, "close conn");
	net_check(xft_close_socket(cli).ok, "close client");
	net_check(xft_close_socket(srv).ok, "close server");
}
