/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_tcp_roundtrip.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_tcp_roundtrip(void)
{
	t_net_test	s;

	net_tcp_pair(s.fds, 47201);
	s.w = xft_tcp_writer(&s.tcp_w, s.fds[1],
			xft_fatptr(s.wbuf, sizeof(s.wbuf)));
	s.r = xft_tcp_reader(&s.tcp_r, s.fds[2],
			xft_fatptr(s.rbuf, sizeof(s.rbuf)));
	net_check(xft_writer_drain_all(&s.w,
			xft_fatptr((const t_u8 *)"hello ", 6)).ok
		&& xft_writer_drain_all(&s.w, xft_fatptr((const t_u8 *)"world", 5)).ok
		&& xft_writer_flush(&s.w).ok, "tcp writer drain_all + flush");
	net_check(xft_reader_read_all(&s.r, xft_fatptr(s.got, 11)).ok,
		"tcp reader read_all");
	net_check(xft_memcmp(s.got, "hello world", 11) == 0, "tcp roundtrip bytes");
	net_check(xft_close_socket(s.fds[2]).ok, "close conn");
	net_check(xft_close_socket(s.fds[1]).ok, "close client");
	net_check(xft_close_socket(s.fds[0]).ok, "close server");
}
