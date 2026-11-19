/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_udp_oversized.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_udp_oversized(void)
{
	const t_ip_addr	dst = net_lo4(47217);
	t_net_test		s;

	net_udp_pair(s.fds, 47217);
	s.w = xft_udp_writer(&s.udp_w, s.fds[1],
			xft_fatptr(s.wbuf, sizeof(s.wbuf)), &dst);
	s.r = xft_udp_reader(&s.udp_r, s.fds[0],
			xft_fatptr(s.rbuf, sizeof(s.rbuf)));
	net_fill(s.data, 100, 1);
	net_check(xft_writer_drain_all(&s.w, xft_fatptr((const t_u8 *)"x", 1)).ok
		&& xft_writer_drain_all(&s.w, xft_fatptr(s.data, 100)).ok,
		"udp oversized write");
	net_check(xft_reader_read(&s.r, xft_fatptr(s.got, sizeof(s.got)), &s.n).ok
		&& s.n == 1 && s.got[0] == 'x', "udp buffered byte goes out first");
	net_check(xft_reader_read(&s.r, xft_fatptr(s.got, sizeof(s.got)), &s.n).ok
		&& s.n == 100 && xft_memcmp(s.got, s.data, 100) == 0,
		"udp oversized write is its own datagram");
	net_check(xft_close_socket(s.fds[0]).ok && xft_close_socket(s.fds[1]).ok,
		"close udp sockets");
}
