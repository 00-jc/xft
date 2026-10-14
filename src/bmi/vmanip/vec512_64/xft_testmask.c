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
inline t_u8	xft_vtestmask512_64(t_vu64_512 vec, t_u64 b)
{
	return (__builtin_ia32_ptestmq512((t_vs64_512)vec,
			(t_vs64_512)xft_vsplat512_64(b), 0xFF));
}

# else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u8	xft_vtestmask512_64(t_vu64_512 vec, t_u64 b)
{
	return (__builtin_ia32_cmpq512_mask((t_vs64_512)(vec & xft_vsplat512_64(b)),
		(t_vs64_512){}, 4, 0xFF));
}

# endif

#endif
