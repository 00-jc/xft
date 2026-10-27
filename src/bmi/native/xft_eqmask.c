/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_eqmask.c                                       :+:      :+:    :+:   */
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
inline t_nmask	xft_veqmask(t_nvec vec, t_u8 b)
{
	return (xft_veqmask512(vec, b));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask	xft_veqmask(t_nvec vec, t_u8 b)
{
	return (xft_veqmask256(vec, b));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask	xft_veqmask(t_nvec vec, t_u8 b)
{
	return (xft_veqmask128(vec, b));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask	xft_veqmask(t_nvec vec, t_u8 b)
{
	return (xft_vmask((t_nvec)(vec == xft_vsplat(b))));
}

#endif
