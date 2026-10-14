/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_compress_mask.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 12:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec32	xft_vcompress32(t_nvec32a vec, t_nmask32 mask)
{
	return (xft_vcompress512_32(vec, mask));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec32	xft_vcompress32(t_nvec32a vec, t_nmask32 mask)
{
	return (xft_vcompress256_32(vec, mask));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec32	xft_vcompress32(t_nvec32a vec, t_nmask32 mask)
{
	return (xft_vcompress128_32(vec, mask));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec32	xft_vcompress32(t_nvec32a vec, t_nmask32 mask)
{
	t_nvec32	out;
	t_size		i;

	out = (t_nvec32){0};
	i = 0;
	while (mask)
	{
		out[i++] = vec[xft_memctz_u32(mask)];
		mask &= mask - 1;
	}
	return (out);
}

#endif
