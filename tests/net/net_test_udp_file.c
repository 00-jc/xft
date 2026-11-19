/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_udp_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

static int	udp_expect(t_reader *r, t_buffer scratch, const t_u8 *want,
	t_size n)
{
	t_size	got;

	return (xft_reader_read(r, scratch, &got).ok && got == n
		&& xft_memcmp(scratch.mem, want, n) == 0);
}

void	test_net_udp_file(void)
{
	const t_ip_addr	dst = net_lo4(47213);
	t_net_test		s;
	t_buffer		file;

	file = xft_map_file_into_memory("LICENSE");
	net_check(file.size >= 150 && xft_open_file((const t_u8 *)"LICENSE",
			(t_fileopen_mode){.read = 1}, &s.fd).ok, "open LICENSE");
	net_udp_pair(s.fds, 47213);
	s.w = xft_udp_writer(&s.udp_w, s.fds[1],
			xft_fatptr(s.wbuf, sizeof(s.wbuf)), &dst);
	s.r = xft_fs_reader(&s.fs_r, s.fd, xft_fatptr(s.data, sizeof(s.data)));
	net_check(xft_reader_stream_all(&s.r, &s.w, 150).ok
		&& xft_writer_flush(&s.w).ok,
		"file -> udp writer");
	s.r = xft_udp_reader(&s.udp_r, s.fds[0],
			xft_fatptr(s.rbuf, sizeof(s.rbuf)));
	net_check(udp_expect(&s.r, xft_fatptr(s.got, sizeof(s.got)), file.mem, 64)
		&& udp_expect(&s.r, xft_fatptr(s.got, sizeof(s.got)), file.mem + 64,
			64) && udp_expect(&s.r, xft_fatptr(s.got, sizeof(s.got)),
			file.mem + 128, 22), "file arrives as 64 + 64 + 22 byte datagrams");
	net_check(xft_close_file(s.fd).ok && xft_close_socket(s.fds[0]).ok
		&& xft_close_socket(s.fds[1]).ok, "close file and udp sockets");
	xft_unmap_file_from_memory(file);
}
