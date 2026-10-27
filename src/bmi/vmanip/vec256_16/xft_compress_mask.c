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

#include <xft/types/xft_p_vmanip_types.h>

#if XFT_HAS_512_VEC && defined(__AVX512VBMI2__)

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_vu16_256	xft_vcompress256_16(t_vu16_256a vec, t_u16a mask)
{
	return ((t_vu16_256)__builtin_ia32_compresshi256_mask((t_vs16_256)vec,
			(t_vs16_256){}, mask));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_vu16_256	xft_vcompress256_16(t_vu16_256a vec, t_u16a mask)
{
	t_vu16_256	out;
	t_size		i;

	out = (t_vu16_256){0};
	i = 0;
	while (mask)
	{
		out[i++] = vec[xft_memctz_u32(mask)];
		mask &= mask - 1;
	}
	return (out);
}

#endif
