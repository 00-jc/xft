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

#if defined(__linux__)

# include <xft/bmi.h>
# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline t_u32a	xft__sockaddr_from_ip(const t_ip_addr *ip, t_sockaddr_in6 *sa)
{
	const t_ip_addr			addr = *ip;
	t_sockaddr_in *const	in = (t_sockaddr_in *)sa;

	if (addr.family == xft_ipv4)
	{
		*in = (t_sockaddr_in){.sin_family = xft_af_inet,
			.sin_port = xft_to_be16(addr.v4.port)};
		in->sin_addr = *(const t_u32a *)addr.v4.address.bytes;
		return (sizeof(t_sockaddr_in));
	}
	*sa = (t_sockaddr_in6){.sin6_family = xft_af_inet6,
		.sin6_port = xft_to_be16(addr.v6.port)};
	*(t_ip6 *)sa->sin6_addr = addr.v6.address;
	return (sizeof(t_sockaddr_in6));
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft__ip_from_sockaddr(const t_sockaddr_in6 *sa, t_ip_addr *ip)
{
	const t_sockaddr_in *const	in = (const t_sockaddr_in *)sa;
	t_ip_addr					res;

	if (sa->sin6_family == xft_af_inet6)
	{
		res.family = xft_ipv6;
		res.v6.address = *(const t_ip6 *)sa->sin6_addr;
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
