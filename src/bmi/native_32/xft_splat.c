/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_splat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 12:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec32	xft_vsplat32(t_u32 b)
{
	return (xft_vsplat512_32(b));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec32	xft_vsplat32(t_u32 b)
{
	return (xft_vsplat256_32(b));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec32	xft_vsplat32(t_u32 b)
{
	return (xft_vsplat128_32(b));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec32	xft_vsplat32(t_u32 b)
{
	return ((t_nvec32){} + b);
}

#endif
