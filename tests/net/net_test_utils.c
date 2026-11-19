/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	net_check(int ok, const char *msg)
{
	xft_pin_invariant_msg(ok, xft_fatptr((const t_u8 *)msg, xft_strlen(msg)));
}

t_ip_addr	net_lo4(t_u16a port)
{
	return ((t_ip_addr){.family = xft_ipv4,
		.v4 = {.address = {{127, 0, 0, 1}}, .port = port}});
}

void	net_tcp_pair(t_fd *fds, t_u16a port)
{
	const t_ip_addr	lo = net_lo4(port);
	const t_fd		srv = net_listen(&lo);

	fds[0] = srv;
	fds[1] = net_connect(&lo);
	net_check(xft_accept_socket(srv, nullptr, &fds[2]).ok, "xft_accept_socket");
}

void	net_udp_pair(t_fd *fds, t_u16a port)
{
	const t_ip_addr	a = net_lo4(port);
	const t_ip_addr	b = net_lo4((t_u16a)(port + 1));

	fds[0] = net_udp(&a);
	fds[1] = net_udp(&b);
}

void	net_fill(t_u8 *buf, t_size n, t_u8 seed)
{
	t_size	i;

	i = 0;
	while (i < n)
	{
		buf[i] = (t_u8)(i * 31 + seed);
		++i;
	}
}
