/* ************************************************************************** */
/*                                                                            */
/*                                                      :::      ::::::::     */
/*   xft_testmask.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:26:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/07 11:36:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

# ifndef __clang__

__attribute__((__always_inline__, const, __used__))
inline t_u64a	xft_vtestmask512(t_vu512 vec, t_u8 b)
{
	return (__builtin_ia32_ptestmb512((t_vc512)vec,
			(t_vc512)xft_vsplat512(b), ~0ULL));
}

# else

__attribute__((__always_inline__, const, __used__))
inline t_u64a	xft_vtestmask512(t_vu512 vec, t_u8 b)
{
	return (__builtin_ia32_cmpb512_mask((t_vc512)(vec & xft_vsplat512(b)),
		(t_vc512)xft_vsplat512(0), 4, ~0ULL));
}

# endif

#endif
