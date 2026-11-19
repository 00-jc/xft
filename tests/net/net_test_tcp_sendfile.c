/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_tcp_sendfile.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_tcp_sendfile(void)
{
	t_net_test	s;
	t_buffer	file;

	file = xft_map_file_into_memory("LICENSE");
	net_check(file.size != 0 && file.size < sizeof(s.got), "map LICENSE");
	net_check(xft_open_file((const t_u8 *)"LICENSE", (t_fileopen_mode){
			.read = 1}, &s.fd).ok, "open LICENSE");
	net_tcp_pair(s.fds, 47204);
	s.w = xft_tcp_writer(&s.tcp_w, s.fds[1],
			xft_fatptr(s.wbuf, sizeof(s.wbuf)));
	s.r = xft_fs_reader(&s.fs_r, s.fd, xft_fatptr(s.rbuf, sizeof(s.rbuf)));
	net_check(xft_writer_drain_all(&s.w, xft_fatptr((const t_u8 *)"<", 1)).ok
		&& xft_reader_stream_all(&s.r, &s.w, file.size).ok
		&& xft_writer_flush(&s.w).ok, "file -> tcp writer (sendfile)");
	s.r = xft_tcp_reader(&s.tcp_r, s.fds[2],
			xft_fatptr(s.rbuf, sizeof(s.rbuf)));
	net_check(xft_reader_read_all(&s.r, xft_fatptr(s.got, file.size + 1)).ok
		&& s.got[0] == '<' && xft_memcmp(s.got + 1, file.mem, file.size) == 0,
		"sendfile bytes follow the buffered header");
	net_check(xft_close_file(s.fd).ok, "close LICENSE");
	xft_unmap_file_from_memory(file);
	net_check(xft_close_socket(s.fds[2]).ok, "close conn");
	net_check(xft_close_socket(s.fds[1]).ok, "close client");
	net_check(xft_close_socket(s.fds[0]).ok, "close server");
}
