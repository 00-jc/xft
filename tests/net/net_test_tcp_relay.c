/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_tcp_relay.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_tcp_relay(void)
{
	t_net_test	a;
	t_net_test	b;

	net_fill(a.data, 2000, 3);
	net_tcp_pair(a.fds, 47206);
	net_tcp_pair(b.fds, 47207);
	a.w = xft_tcp_writer(&a.tcp_w, a.fds[1],
			xft_fatptr(a.wbuf, sizeof(a.wbuf)));
	net_check(xft_writer_drain_all(&a.w, xft_fatptr(a.data, 2000))
		&& xft_writer_flush(&a.w) && xft_close_socket(a.fds[1]),
		"relay source");
	a.r = xft_tcp_reader(&a.tcp_r, a.fds[2],
			xft_fatptr(a.rbuf, sizeof(a.rbuf)));
	b.w = xft_tcp_writer(&b.tcp_w, b.fds[1],
			xft_fatptr(b.wbuf, sizeof(b.wbuf)));
	net_check(xft_reader_stream_all(&a.r, &b.w, 2000)
		&& xft_writer_flush(&b.w), "socket -> tcp writer (copy fallback)");
	b.r = xft_tcp_reader(&b.tcp_r, b.fds[2],
			xft_fatptr(b.rbuf, sizeof(b.rbuf)));
	net_check(xft_reader_read_all(&b.r, xft_fatptr(b.got, 2000))
		&& xft_memcmp(b.got, a.data, 2000) == 0, "relayed bytes");
	net_check(xft_close_socket(a.fds[2]) && xft_close_socket(a.fds[0])
		&& xft_close_socket(b.fds[2]) && xft_close_socket(b.fds[1])
		&& xft_close_socket(b.fds[0]), "close relay sockets");
}
