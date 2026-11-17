/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net(t_test *t)
{
	xft_test_print(t, "Testing net...\n");
	net_check(xft_init_sockets(), "xft_init_sockets");
	test_net_tcp_roundtrip();
	test_net_tcp_peer();
	test_net_tcp_v6();
	test_net_tcp_sendfile();
	test_net_tcp_reader();
	test_net_tcp_relay();
	test_net_tcp_refused();
	test_net_tcp_bound_client();
	test_net_udp_datagrams();
	test_net_udp_oversized();
	test_net_udp_file();
	test_net_udp_discard_stream();
	test_net_udp_connected();
	xft_test_print(t, "  net: OK\n");
}
