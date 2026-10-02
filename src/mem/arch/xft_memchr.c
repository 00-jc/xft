/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 15:06:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

#if XFT_HAS_512_VEC

__attribute__((__nonnull__ (1), pure))
t_any	xft_memchr(t_cany restrict ptr, int c, t_size n)
{
	if (n >= sizeof(t_vu512a))
		return (xft_memchr_512(ptr, c, n));
	else if (n >= sizeof(t_vu256a))
		return (xft_memchr_256(ptr, c, n));
	else if (n >= sizeof(t_vu128a))
		return (xft_memchr_128(ptr, c, n));
	else
		return (xft_memchr_minimal(ptr, (t_u8)c, n));
}

#elif XFT_HAS_256_VEC

__attribute__((__nonnull__ (1), pure))
t_any	xft_memchr(t_cany restrict ptr, int c, t_size n)
{
	if (n >= sizeof(t_vu256a))
		return (xft_memchr_256(ptr, c, n));
	else if (n >= sizeof(t_vu128a))
		return (xft_memchr_128(ptr, c, n));
	else
		return (xft_memchr_minimal(ptr, (t_u8)c, n));
}

#elif XFT_HAS_128_VEC

__attribute__((__nonnull__ (1), pure))
t_any	xft_memchr(t_cany restrict ptr, int c, t_size n)
{
	if (n >= sizeof(t_vu128a))
		return (xft_memchr_128(ptr, c, n));
	else
		return (xft_memchr_minimal(ptr, (t_u8)c, n));
}

#else

__attribute__((__nonnull__ (1), pure))
t_any	xft_memchr(t_cany restrict ptr, int c, t_size n)
{
	return (xft_memchr_minimal(ptr, (t_u8)c, n));
}

#endif
