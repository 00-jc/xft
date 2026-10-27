/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_rangemask.c                                    :+:      :+:    :+:   */
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
inline t_nmask32	xft_vrangemask32(t_nvec32a v, t_u32 lo, t_u32 hi)
{
	return (xft_vrangemask512_32(v, lo, hi));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask32	xft_vrangemask32(t_nvec32a v, t_u32 lo, t_u32 hi)
{
	return (xft_vrangemask256_32(v, lo, hi));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask32	xft_vrangemask32(t_nvec32a v, t_u32 lo, t_u32 hi)
{
	return (xft_vrangemask128_32(v, lo, hi));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask32	xft_vrangemask32(t_nvec32a v, t_u32 lo, t_u32 hi)
{
	return (xft_vmask32((t_nvec32)(v - xft_vsplat32(lo)
			<= xft_vsplat32(hi - lo))));
}

#endif
