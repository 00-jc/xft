/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_udp_discard_stream.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_udp_discard_stream(void)
{
	const t_ip_addr		dst = net_lo4(47215);
	t_net_test			s;
	t_writer_ctx_memory	m;
	t_writer			mw;

	net_udp_pair(s.fds, 47215);
	s.w = xft_udp_writer(&s.udp_w, s.fds[1],
			xft_fatptr(s.wbuf, sizeof(s.wbuf)), &dst);
	s.r = xft_udp_reader(&s.udp_r, s.fds[0],
			xft_fatptr(s.rbuf, sizeof(s.rbuf)));
	net_check(xft_writer_drain_all(&s.w, xft_fatptr((const t_u8 *)"123456789",
				9)).ok && xft_writer_flush(&s.w).ok
		&& xft_reader_discard(&s.r, 4, &s.n).ok && s.n == 4,
		"udp discard reports at most limit");
	net_check(xft_writer_drain_all(&s.w, xft_fatptr((const t_u8 *)"stream!",
				7)).ok && xft_writer_flush(&s.w).ok, "udp send for stream");
	mw = xft_mem_writer(&m, xft_fatptr(s.got, 32));
	net_check(xft_reader_stream(&s.r, &mw, 100, &s.n).ok && s.n == 7
		&& xft_memcmp(s.got, "stream!", 7) == 0,
		"udp discard dropped the whole datagram, stream gets the next");
	net_check(xft_close_socket(s.fds[0]).ok && xft_close_socket(s.fds[1]).ok,
		"close udp sockets");
}
