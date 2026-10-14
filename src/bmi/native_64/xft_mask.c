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

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vmask64(t_nvec64 vec)
{
	return (xft_vmask512_64(vec));
}

#elif XFT_HAS_256_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vmask64(t_nvec64 vec)
{
	return (xft_vmask256_64(vec));
}

#elif XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vmask64(t_nvec64 vec)
{
	return (xft_vmask128_64(vec));
}

#else

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_nmask64	xft_vmask64(t_nvec64 vec)
{
	t_nmask64	out;
	t_size		i;

	out = 0;
	i = 0;
	while (i < (XFT_NVEC_SIZE / 8))
	{
		out |= (t_nmask64)((vec[i] >> 63) & 1) << i;
		i++;
	}
	return (out);
}

#endif
