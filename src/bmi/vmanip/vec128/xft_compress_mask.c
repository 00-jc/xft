/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_compress_mask.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 17:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 20:10:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC && defined(__AVX512VBMI2__)

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_vu128	xft_vcompress128(t_vu128a vec, t_u16a mask)
{
	return ((t_vu128)__builtin_ia32_compressqi128_mask((t_vc128)vec,
			(t_vc128)xft_vsplat128(0), mask));
}

#elif XFT_HAS_128_VEC

/*
 *	Recreating this with full simd-register stuff
 *	generically is too much and bloats the size a LOT
 *	since we need pshuf lut tables, @Revise for a workaround.
 */

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_vu128	xft_vcompress128(t_vu128a vec, t_u16a mask)
{
	t_vu128a	out;
	t_size		i;

	out = (t_vu128a){0};
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
