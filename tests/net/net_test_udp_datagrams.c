/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_udp_datagrams.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_udp_datagrams(void)
{
	const t_ip_addr	dst = net_lo4(47211);
	t_net_test		s;

	net_udp_pair(s.fds, 47211);
	s.w = xft_udp_writer(&s.udp_w, s.fds[1],
			xft_fatptr(s.wbuf, sizeof(s.wbuf)), &dst);
	s.r = xft_udp_reader(&s.udp_r, s.fds[0],
			xft_fatptr(s.rbuf, sizeof(s.rbuf)));
	net_check(xft_writer_drain_all(&s.w,
			xft_fatptr((const t_u8 *)"hello ", 6)).ok
		&& xft_writer_drain_all(&s.w, xft_fatptr((const t_u8 *)"world", 5)).ok
		&& xft_writer_flush(&s.w).ok, "udp buffered send");
	net_check(xft_reader_read(&s.r, xft_fatptr(s.got, sizeof(s.got)), &s.n).ok
		&& s.n == 11 && xft_memcmp(s.got, "hello world", 11) == 0,
		"udp flush sends one datagram");
	net_check(s.udp_r.ip.family == xft_ipv4 && s.udp_r.ip.v4.port == 47212,
		"udp reader records the sender");
	net_check(xft_close_socket(s.fds[0]).ok && xft_close_socket(s.fds[1]).ok,
		"close udp sockets");
}
