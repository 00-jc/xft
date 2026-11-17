/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_net.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 03:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_NET_H
# define XFT_P_NET_H

# include <xft/net.h>
# if defined(_WIN32)
#  include <winsock2.h>
#  include <ws2tcpip.h>
# else
#  include <xft/types/xft_p_syscalls_types.h>
# endif

# if defined(_WIN32)

t_u32a		xft__sockaddr_from_ip(const t_ip_addr *endpoint,\
				SOCKADDR_IN6 *sockaddr)\
				__attribute__((__nonnull__(1, 2)));

void		xft__ip_from_sockaddr(const SOCKADDR_IN6 *sockaddr,\
				t_ip_addr *endpoint)\
				__attribute__((__nonnull__(1, 2)));

# else

t_u32a		xft__sockaddr_from_ip(const t_ip_addr *endpoint,\
				t_sockaddr_in6 *sockaddr)\
				__attribute__((__nonnull__(1, 2)));

void		xft__ip_from_sockaddr(const t_sockaddr_in6 *sockaddr,\
				t_ip_addr *endpoint)\
				__attribute__((__nonnull__(1, 2)));

# endif

#endif
