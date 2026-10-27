/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_eqmask.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 12:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/types/xft_p_vmanip_types.h>

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u8	xft_veqmask128_32(t_vu32_128 vec, t_u32 b)
{
	return (__builtin_ia32_ucmpd128_mask((t_vs32_128)vec,
			(t_vs32_128)xft_vsplat128_32(b), 0, 0xFF));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u8	xft_veqmask128_32(t_vu32_128 vec, t_u32 b)
{
	return (xft_vmask128_32((t_vu32_128)(vec == xft_vsplat128_32(b))));
}

#endif
