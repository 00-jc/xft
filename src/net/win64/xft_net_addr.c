/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_net_addr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_net.h>

#if defined(_WIN32)

# include <xft/bmi.h>
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>
# include <ws2tcpip.h>

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline t_u32a	xft__sockaddr_from_ip(const t_ip_addr *ip, SOCKADDR_IN6 *sa)
{
	const t_ip_addr		addr = *ip;
	SOCKADDR_IN *const	in = (SOCKADDR_IN *)sa;

	if (addr.family == xft_ipv4)
	{
		*in = (SOCKADDR_IN){.sin_family = AF_INET,
			.sin_port = xft_to_be16(addr.v4.port)};
		in->sin_addr = *(const IN_ADDR *)addr.v4.address.bytes;
		return (sizeof(SOCKADDR_IN));
	}
	*sa = (SOCKADDR_IN6){.sin6_family = AF_INET6,
		.sin6_port = xft_to_be16(addr.v6.port)};
	sa->sin6_addr = *(const IN6_ADDR *)addr.v6.address.bytes;
	return (sizeof(SOCKADDR_IN6));
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft__ip_from_sockaddr(const SOCKADDR_IN6 *sa, t_ip_addr *ip)
{
	const SOCKADDR_IN *const	in = (const SOCKADDR_IN *)sa;
	t_ip_addr					res;

	if (sa->sin6_family == AF_INET6)
	{
		res.family = xft_ipv6;
		res.v6.address = *(const t_ip6 *)&sa->sin6_addr;
		res.v6.port = xft_from_be16(sa->sin6_port);
		*ip = res;
		return ;
	}
	res.family = xft_ipv4;
	res.v4.address = *(const t_ip4 *)&in->sin_addr;
	res.v4.port = xft_from_be16(in->sin_port);
	*ip = res;
}

#endif
