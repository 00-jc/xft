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
inline t_nvec64	xft_vsplat64(t_u64 b)
{
	return (xft_vsplat512_64(b));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec64	xft_vsplat64(t_u64 b)
{
	return (xft_vsplat256_64(b));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec64	xft_vsplat64(t_u64 b)
{
	return (xft_vsplat128_64(b));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nvec64	xft_vsplat64(t_u64 b)
{
	return ((t_nvec64){} + b);
}

#endif
