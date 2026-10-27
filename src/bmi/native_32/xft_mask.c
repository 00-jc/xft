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
inline t_nmask32	xft_vmask32(t_nvec32 vec)
{
	return (xft_vmask512_32(vec));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask32	xft_vmask32(t_nvec32 vec)
{
	return (xft_vmask256_32(vec));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask32	xft_vmask32(t_nvec32 vec)
{
	return (xft_vmask128_32(vec));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask32	xft_vmask32(t_nvec32 vec)
{
	t_nmask32	out;
	t_size		i;

	out = 0;
	i = 0;
	while (i < (XFT_NVEC_SIZE / 4))
	{
		out |= (t_nmask32)((vec[i] >> 31) & 1) << i;
		i++;
	}
	return (out);
}

#endif
