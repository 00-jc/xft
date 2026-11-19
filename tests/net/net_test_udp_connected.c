/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_udp_connected.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_udp_connected(void)
{
	const t_ip_addr	recv_addr = net_lo4(47222);
	const t_ip_addr	send_addr = net_lo4(47223);
	t_net_test		s;

	s.fds[0] = net_udp(&recv_addr);
	s.fds[1] = net_udp(&send_addr);
	net_check(xft_connect_socket(s.fds[1], &recv_addr,
			(t_connect_options){0}).ok,
		"connect a bound udp socket");
	s.w = xft_udp_writer(&s.udp_w, s.fds[1],
			xft_fatptr(s.wbuf, sizeof(s.wbuf)), &recv_addr);
	s.r = xft_udp_reader(&s.udp_r, s.fds[0],
			xft_fatptr(s.rbuf, sizeof(s.rbuf)));
	net_check(xft_writer_drain_all(&s.w, xft_fatptr((const t_u8 *)"ping", 4)).ok
		&& xft_writer_flush(&s.w).ok, "send on bound + connected udp");
	net_check(xft_reader_read(&s.r, xft_fatptr(s.got, sizeof(s.got)), &s.n).ok
		&& s.n == 4 && s.udp_r.ip.v4.port == 47223,
		"datagram comes from the bound port");
	net_check(xft_close_socket(s.fds[0]).ok && xft_close_socket(s.fds[1]).ok,
		"close connected udp sockets");
}
