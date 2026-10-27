/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_compress_mask.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 16:59:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 20:10:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/types/xft_p_vmanip_types.h>

#if XFT_HAS_512_VEC && defined(__AVX512VBMI2__)

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_vu512	xft_vcompress512(t_vu512a vec, t_u64a mask)
{
	return ((t_vu512)__builtin_ia32_compressqi512_mask((t_vc512)vec,
			(t_vc512)xft_vsplat512(0), mask));
}

#elif XFT_HAS_512_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_vu512	xft_vcompress512(t_vu512a vec, t_u64a mask)
{
	t_vu512a	out;
	t_size		i;

	out = (t_vu512a){0};
	i = 0;
	while (mask)
	{
		if (i >= sizeof(mask) << 3)
			__builtin_unreachable();
		out[i++] = vec[xft_memctz_u64(mask)];
		mask &= mask - 1;
	}
	return (out);
}

#endif
