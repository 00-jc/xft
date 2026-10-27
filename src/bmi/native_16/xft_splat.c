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

#include <xft/types/xft_p_vmanip_types.h>

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec16	xft_vsplat16(t_u16 b)
{
	return (xft_vsplat512_16(b));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec16	xft_vsplat16(t_u16 b)
{
	return (xft_vsplat256_16(b));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec16	xft_vsplat16(t_u16 b)
{
	return (xft_vsplat128_16(b));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec16	xft_vsplat16(t_u16 b)
{
	return ((t_nvec16){} + b);
}

#endif
