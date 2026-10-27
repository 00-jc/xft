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
inline t_u16a	xft_veqmask256_16(t_vu16_256 vec, t_u16 b)
{
	return (__builtin_ia32_ucmpw256_mask((t_vs16_256)vec,
			(t_vs16_256)xft_vsplat256_16(b), 0, 0xFFFF));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u16a	xft_veqmask256_16(t_vu16_256 vec, t_u16 b)
{
	return (xft_vmask256_16((t_vu16_256)(vec == xft_vsplat256_16(b))));
}

#endif
