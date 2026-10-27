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
inline t_nmask16	xft_vtestmask16(t_nvec16 vec, t_u16 b)
{
	return (xft_vtestmask512_16(vec, b));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask16	xft_vtestmask16(t_nvec16 vec, t_u16 b)
{
	return (xft_vtestmask256_16(vec, b));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask16	xft_vtestmask16(t_nvec16 vec, t_u16 b)
{
	return (xft_vtestmask128_16(vec, b));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask16	xft_vtestmask16(t_nvec16 vec, t_u16 b)
{
	return (xft_vmask16((t_nvec16)((vec & xft_vsplat16(b)) != 0)));
}

#endif
