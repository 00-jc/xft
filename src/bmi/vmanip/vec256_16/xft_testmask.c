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
inline t_u16a	xft_vtestmask256_16(t_vu16_256 vec, t_u16 b)
{
	return (__builtin_ia32_ptestmw256((t_vs16_256)vec,
			(t_vs16_256)xft_vsplat256_16(b), 0xFFFF));
}

# else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u16a	xft_vtestmask256_16(t_vu16_256 vec, t_u16 b)
{
	return (__builtin_ia32_cmpw256_mask((t_vs16_256)(vec & xft_vsplat256_16(b)),
		(t_vs16_256){}, 4, 0xFFFF));
}

# endif

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u16a	xft_vtestmask256_16(t_vu16_256 vec, t_u16 b)
{
	return (xft_vmask256_16((t_vu16_256)((vec & xft_vsplat256_16(b)) != 0)));
}

#endif
