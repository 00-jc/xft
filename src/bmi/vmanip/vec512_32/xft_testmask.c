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

#include <xft/types/xft_p_vmanip_types.h>

#if XFT_HAS_512_VEC

# ifndef __clang__

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u16a	xft_vtestmask512_32(t_vu32_512 vec, t_u32 b)
{
	return (__builtin_ia32_ptestmd512((t_vs32_512)vec,
			(t_vs32_512)xft_vsplat512_32(b), 0xFFFF));
}

# else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u16a	xft_vtestmask512_32(t_vu32_512 vec, t_u32 b)
{
	return (__builtin_ia32_cmpd512_mask((t_vs32_512)(vec & xft_vsplat512_32(b)),
		(t_vs32_512){}, 4, 0xFFFF));
}

# endif

#endif
