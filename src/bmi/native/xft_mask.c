/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mask.c                                         :+:      :+:    :+:   */
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
inline t_nmask	xft_vmask(t_nvec vec)
{
	return (xft_vmask512(vec));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask	xft_vmask(t_nvec vec)
{
	return (xft_vmask256(vec));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask	xft_vmask(t_nvec vec)
{
	return (xft_vmask128(vec));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask	xft_vmask(t_nvec vec)
{
	return ((t_nmask)(((((t_u64)vec & 0x8080808080808080ULL) >> 7)
			* 0x0102040810204080ULL) >> 56));
}

#endif
