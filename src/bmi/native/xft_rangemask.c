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

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask	xft_vrangemask(t_nvec v, t_u8 lo, t_u8 hi)
{
	return (xft_vrangemask512(v, lo, hi));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask	xft_vrangemask(t_nvec v, t_u8 lo, t_u8 hi)
{
	return (xft_vrangemask256(v, lo, hi));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask	xft_vrangemask(t_nvec v, t_u8 lo, t_u8 hi)
{
	return (xft_vrangemask128(v, lo, hi));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask	xft_vrangemask(t_nvec v, t_u8 lo, t_u8 hi)
{
	return (xft_vmask((t_nvec)(v - xft_vsplat(lo)
			<= xft_vsplat(hi - lo))));
}

#endif
