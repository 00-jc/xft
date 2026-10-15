/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_compress_mask.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 17:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 20:10:41 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_vu256	xft_vcompress256(t_vu256a vec, t_u32a mask)
{
	return ((t_vu256)__builtin_ia32_compressqi256_mask((t_vc256)vec,
			(t_vc256)xft_vsplat256(0), mask));
}

#elif XFT_HAS_256_VEC

/*
 *	Recreating this with full simd-register stuff
 *	generically is too much and bloats the size a LOT
 *	since we need pshuf lut tables, @Revise for a workaround.
 */

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_vu256	xft_vcompress256(t_vu256a vec, t_u32a mask)
{
	t_vu256a	out;
	t_size		i;

	out = (t_vu256a){0};
	i = 0;
	while (mask)
	{
		if (i >= sizeof(mask) << 3)
			__builtin_unreachable();
		out[i++] = vec[xft_memctz_u32(mask)];
		mask &= mask - 1;
	}
	return (out);
}

#endif
