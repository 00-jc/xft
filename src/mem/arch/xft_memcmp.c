/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 15:06:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1, 2)))
t_ssize	xft_memcmp(t_cany restrict const dest,
	t_cany restrict src, t_size n)
{
	if (n >= sizeof(t_vu512a))
		return (xft_memcmp_512(dest, src, n));
	else if (n >= sizeof(t_vu256a))
		return (xft_memcmp_256(dest, src, n));
	else if (n >= sizeof(t_vu128a))
		return (xft_memcmp_128(dest, src, n));
	else
		return (xft_memcmp_minimal(dest, src, 0, n));
}

#elif XFT_HAS_256_VEC

__attribute__((__nonnull__(1, 2)))
t_ssize	xft_memcmp(t_cany restrict const dest,
	t_cany restrict src, t_size n)
{
	if (n >= sizeof(t_vu256a))
		return (xft_memcmp_256(dest, src, n));
	else if (n >= sizeof(t_vu128a))
		return (xft_memcmp_128(dest, src, n));
	else
		return (xft_memcmp_minimal(dest, src, 0, n));
}

#elif XFT_HAS_128_VEC

__attribute__((__nonnull__(1, 2)))
t_ssize	xft_memcmp(t_cany restrict const dest,
	t_cany restrict src, t_size n)
{
	if (n >= sizeof(t_vu128a))
		return (xft_memcmp_128(dest, src, n));
	else
		return (xft_memcmp_minimal(dest, src, 0, n));
}

#else

__attribute__((__nonnull__(1, 2)))
t_ssize	xft_memcmp(t_cany restrict const dest,
	t_cany restrict src, t_size n)
{
	return (xft_memcmp_minimal(dest, src, 0, n));
}

#endif
