/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_bswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if !defined(__x86_64__) && !defined(__aarch64__)

__attribute__((__always_inline__, const, __used__))
inline t_u16a	xft_bswap16(t_u16a x)
{
	return ((t_u16a)(((x & 0xFF00U) >> 8U)
		| ((x & 0x00FFU) << 8U)));
}

__attribute__((__always_inline__, const, __used__))
inline t_u32a	xft_bswap32(t_u32a x)
{
	return ((t_u32a)(((x & 0xFF000000) >> 24)
		| ((x & 0x00FF0000) >> 8)
		| ((x & 0x0000FF00) << 8)
		| ((x & 0x000000FF) << 24)));
}

__attribute__((__always_inline__, const, __used__))
inline t_u64a	xft_bswap64(t_u64a x)
{
	return (((x << 56) & 0xff00000000000000ULL)
		| ((x << 40) & 0x00ff000000000000ULL)
		| ((x << 24) & 0x0000ff0000000000ULL)
		| ((x << 8) & 0x000000ff00000000ULL)
		| ((x >> 8) & 0x00000000ff000000ULL)
		| ((x >> 24) & 0x0000000000ff0000ULL)
		| ((x >> 40) & 0x000000000000ff00ULL)
		| ((x >> 56) & 0x00000000000000ffULL));
}

#endif
