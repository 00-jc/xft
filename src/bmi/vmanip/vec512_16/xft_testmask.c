/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_testmask.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 12:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

# ifndef __clang__

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u32a	xft_vtestmask512_16(t_vu16_512 vec, t_u16 b)
{
	return (__builtin_ia32_ptestmw512((t_vs16_512)vec,
			(t_vs16_512)xft_vsplat512_16(b), 0xFFFFFFFF));
}

# else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u32a	xft_vtestmask512_16(t_vu16_512 vec, t_u16 b)
{
	return (__builtin_ia32_cmpw512_mask((t_vs16_512)(vec & xft_vsplat512_16(b)),
		(t_vs16_512){}, 4, 0xFFFFFFFF));
}

# endif

#endif
