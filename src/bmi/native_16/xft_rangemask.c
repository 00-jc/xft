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
inline t_nmask16	xft_vrangemask16(t_nvec16a v, t_u16 lo, t_u16 hi)
{
	return (xft_vrangemask512_16(v, lo, hi));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask16	xft_vrangemask16(t_nvec16a v, t_u16 lo, t_u16 hi)
{
	return (xft_vrangemask256_16(v, lo, hi));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask16	xft_vrangemask16(t_nvec16a v, t_u16 lo, t_u16 hi)
{
	return (xft_vrangemask128_16(v, lo, hi));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask16	xft_vrangemask16(t_nvec16a v, t_u16 lo, t_u16 hi)
{
	return (xft_vmask16((t_nvec16)(v - xft_vsplat16(lo)
			<= xft_vsplat16(hi - lo))));
}

#endif
