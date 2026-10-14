/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_compress_mask.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 20:01:40 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 20:06:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#ifdef XFT_HAS_512_VEC

__attribute__((const, __always_inline__, __used__))
inline t_nvec	xft_vcompress(t_nvec vec, t_nmask mask)
{
	return (xft_vcompress512(vec, mask));
}

#elif defined(XFT_HAS_256_VEC)

__attribute__((const, __always_inline__, __used__))
inline t_nvec	xft_vcompress(t_nvec vec, t_nmask mask)
{
	return (xft_vcompress256(vec, mask));
}

#elif defined(XFT_HAS_128_VEC)

__attribute__((const, __always_inline__, __used__))
inline t_nvec	xft_vcompress(t_nvec vec, t_nmask mask)
{
	return (xft_vcompress128(vec, mask));
}

#else

__attribute__((const, __always_inline__, __used__))
inline t_nvec	xft_vcompress(t_nvec vec, t_nmask mask)
{
	t_nvec	out;
	t_size	i;

	out = (t_nvec){0};
	i = 0;
	while (mask)
	{
		if (i >= sizeof(mask) << 3)
			__builtin_unreachable();
		out[i++] = vec[xft_memctz_u16(mask)];
		mask &= mask - 1;
	}
	return (out);
}

#endif
