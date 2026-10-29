/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_bswap_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>

#if __has_builtin(__builtin_bswap16)

__attribute__((__always_inline__, const, __used__))
inline t_u16a	xft_bswap16(t_u16a x)
{
	return (__builtin_bswap16(x));
}

__attribute__((__always_inline__, const, __used__))
inline t_u32a	xft_bswap32(t_u32a x)
{
	return (__builtin_bswap32(x));
}

__attribute__((__always_inline__, const, __used__))
inline t_u64a	xft_bswap64(t_u64a x)
{
	return (__builtin_bswap64(x));
}

#endif
