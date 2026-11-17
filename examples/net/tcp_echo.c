/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 02:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 02:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft.h>

static t_u8	g_rbuf[4096];
static t_u8	g_wbuf[4096];

__attribute__((__flatten__))
static void	echo(t_fd conn)
{
	t_reader_ctx_tcp	rctx;
	t_writer_ctx_tcp	wctx;
	t_reader			r;
	t_writer			w;
	t_size				n;

	r = xft_tcp_reader(&rctx, conn, xft_fatptr(g_rbuf, sizeof(g_rbuf)));
	w = xft_tcp_writer(&wctx, conn, xft_fatptr(g_wbuf, sizeof(g_wbuf)));
	if (xft_reader_stream(&r, &w, (t_size)-1, &n))
		(void)xft_writer_flush(&w);
	(void)xft_close_socket(conn);
}

static t_fd	listen_on(t_u16a port)
{
	const t_ip_addr	any = {.family = xft_ipv4, .v4 = {.port = port}};
	t_fd			server;

	if (!xft_init_sockets()
		|| !xft_open_socket(xft_ipv4, xft_socket_tcp, &server))
		xft_exit_process(1);
	if (!xft_bind_socket(server, &any, (t_ip_bind_opts){0})
		|| !xft_listen_socket(server, 0))
		xft_exit_process(1);
	return (server);
}

void	xft_main(const t_any *__restrict__ const sp)
{
	const t_fd	server = listen_on(7777);
	t_fd		conn;

	(void)sp;
	while (xft_accept_socket(server, nullptr, &conn))
		echo(conn);
	(void)xft_close_socket(server);
	xft_exit_process(1);
}
