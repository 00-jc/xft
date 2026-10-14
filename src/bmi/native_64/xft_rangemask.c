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
inline t_nmask64	xft_vrangemask64(t_nvec64a v, t_u64 lo, t_u64 hi)
{
	return (xft_vrangemask512_64(v, lo, hi));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vrangemask64(t_nvec64a v, t_u64 lo, t_u64 hi)
{
	return (xft_vrangemask256_64(v, lo, hi));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vrangemask64(t_nvec64a v, t_u64 lo, t_u64 hi)
{
	return (xft_vrangemask128_64(v, lo, hi));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vrangemask64(t_nvec64a v, t_u64 lo, t_u64 hi)
{
	return (xft_vmask64((t_nvec64)(v - xft_vsplat64(lo)
			<= xft_vsplat64(hi - lo))));
}

#endif
