/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_tcp_reader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_tcp_reader(void)
{
	t_net_test			s;
	t_writer_ctx_memory	m;

	net_fill(s.data, 3000, 7);
	net_tcp_pair(s.fds, 47205);
	s.w = xft_tcp_writer(&s.tcp_w, s.fds[1],
			xft_fatptr(s.wbuf, sizeof(s.wbuf)));
	net_check(xft_writer_drain_all(&s.w, xft_fatptr(s.data, 3000))
		&& xft_writer_flush(&s.w) && xft_close_socket(s.fds[1]),
		"tcp send 3000 then close");
	s.r = xft_tcp_reader(&s.tcp_r, s.fds[2],
			xft_fatptr(s.rbuf, sizeof(s.rbuf)));
	net_check(xft_reader_read_all(&s.r, xft_fatptr(s.got, 1000))
		&& xft_reader_discard_all(&s.r, 1000), "tcp read_all + discard_all");
	s.w = xft_mem_writer(&m, xft_fatptr(s.got + 1000, 2000));
	net_check(xft_reader_stream(&s.r, &s.w, (t_size)-1, &s.n) && s.n == 1000,
		"tcp stream to end of stream");
	net_check(xft_memcmp(s.got, s.data, 1000) == 0
		&& xft_memcmp(s.got + 1000, s.data + 2000, 1000) == 0,
		"tcp reader skips exactly the discarded bytes");
	net_check(xft_reader_read(&s.r, xft_fatptr(s.got, 8), &s.n) && s.n == 0,
		"tcp read at end of stream");
	net_check(xft_close_socket(s.fds[2]), "close conn");
	net_check(xft_close_socket(s.fds[0]), "close server");
}
