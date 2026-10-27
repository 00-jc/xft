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

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vtestmask64(t_nvec64 vec, t_u64 b)
{
	return (xft_vtestmask512_64(vec, b));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vtestmask64(t_nvec64 vec, t_u64 b)
{
	return (xft_vtestmask256_64(vec, b));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vtestmask64(t_nvec64 vec, t_u64 b)
{
	return (xft_vtestmask128_64(vec, b));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vtestmask64(t_nvec64 vec, t_u64 b)
{
	return (xft_vmask64((t_nvec64)((vec & xft_vsplat64(b)) != 0)));
}

#endif
