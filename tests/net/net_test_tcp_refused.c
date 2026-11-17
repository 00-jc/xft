/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_test_tcp_refused.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/net/net_test.h"

void	test_net_tcp_refused(void)
{
	const t_ip_addr	lo = net_lo4(47208);
	t_fd			fd;

	net_check(xft_open_socket(xft_ipv4, xft_socket_tcp, &fd),
		"xft_open_socket");
	net_check(!xft_connect_socket(fd, &lo, (t_connect_options){0}),
		"connect to a closed port fails");
	net_check(xft_close_socket(fd), "close refused socket");
}
