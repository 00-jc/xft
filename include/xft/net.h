/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:26:19 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 15:55:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NET_H
# define NET_H

# include <xft/primitives.h>
# include <xft/files.h>

typedef enum e_ip_family : t_u8
{
	xft_ipv4,
	xft_ipv6,
}	t_ip_family;

typedef enum e_socket_type : t_u8
{
	xft_socket_tcp,
	xft_socket_udp,
}	t_socket_type;

typedef struct s_ip_bind_opts
{
	bool	allow_broadcast	: 1;
	bool	ipv6_only		: 1;
}	t_ip_bind_opts;

typedef struct s_connect_options
{
	bool			has_timeout;
	t_u64a			timeout_ms;
}	t_connect_options;

typedef struct s_ip4
{
	t_u8		bytes[4];
}	t_ip4;

typedef struct s_ip6
{
	t_u8		bytes[16];
}	t_ip6;

typedef struct s_ipv4
{
	t_ip4		address;
	t_u16a		port;
}	t_ipv4;

typedef struct s_ipv6
{
	t_ip6		address;
	t_u16a		port;
}	t_ipv6;

typedef struct s_ip_addr
{
	t_ip_family	family;
	union
	{
		t_ipv4	v4;
		t_ipv6	v6;
	};
}	t_ip_addr;

t_result	xft_open_socket(t_ip_family family, t_socket_type type,\
				t_fd *sock)\
				__attribute__((__nonnull__(3)));

t_result	xft_bind_socket(t_fd sock, const t_ip_addr *addr,\
				t_ip_bind_opts opts)\
				__attribute__((__nonnull__(2)));

t_result	xft_listen_socket(t_fd sock, t_u32a backlog);

t_result	xft_connect_socket(t_fd sock, const t_ip_addr *addr,\
				t_connect_options opts)\
				__attribute__((__nonnull__(2)));

t_result	xft_accept_socket(t_fd server, t_ip_addr *peer, t_fd *conn)\
				__attribute__((__nonnull__(3)));

t_result	xft_close_socket(t_fd sock);

#endif
