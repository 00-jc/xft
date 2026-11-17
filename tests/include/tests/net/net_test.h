/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NET_TEST_H
# define NET_TEST_H

# include <xft/test.h>
# include <xft/net.h>
# include <xft/io.h>
# include <xft/mem.h>
# include <xft/cstr.h>
# include <xft/hint.h>
# include <xft/rt.h>

typedef struct s_net_test
{
	t_fd				fds[3];
	t_fd				fd;
	t_size				n;
	t_writer			w;
	t_reader			r;
	t_u8				wbuf[64];
	t_u8				rbuf[256];
	t_u8				data[4096];
	t_u8				got[4096];
	t_writer_ctx_tcp	tcp_w;
	t_reader_ctx_tcp	tcp_r;
	t_writer_ctx_udp	udp_w;
	t_reader_ctx_udp	udp_r;
	t_reader_fs			fs_r;
}	t_net_test;

void		net_check(int ok, const char *msg);
t_ip_addr	net_lo4(t_u16a port);
void		net_tcp_pair(t_fd *fds, t_u16a port);
void		net_udp_pair(t_fd *fds, t_u16a port);
void		net_fill(t_u8 *buf, t_size n, t_u8 seed);
t_fd		net_listen(const t_ip_addr *addr);
t_fd		net_connect(const t_ip_addr *addr);
t_fd		net_udp(const t_ip_addr *addr);
void		test_net_tcp_roundtrip(void);
void		test_net_tcp_peer(void);
void		test_net_tcp_v6(void);
void		test_net_tcp_sendfile(void);
void		test_net_tcp_reader(void);
void		test_net_tcp_relay(void);
void		test_net_tcp_refused(void);
void		test_net_tcp_bound_client(void);
void		test_net_udp_connected(void);
void		test_net_udp_datagrams(void);
void		test_net_udp_oversized(void);
void		test_net_udp_file(void);
void		test_net_udp_discard_stream(void);
void		test_net(t_test *t);

#endif
