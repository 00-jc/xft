/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_iota.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 12:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec32a	xft_viota32(void)
{
	return (xft_viota512_32());
}

#elif XFT_HAS_256_VEC

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec32a	xft_viota32(void)
{
	return (xft_viota256_32());
}

#elif XFT_HAS_128_VEC

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec32a	xft_viota32(void)
{
	return (xft_viota128_32());
}

#else

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec32a	xft_viota32(void)
{
	t_nvec32a	out;
	t_size		i;

	i = 0;
	while (i < (XFT_NVEC_SIZE / 4))
	{
		out[i] = (t_u32)i;
		i++;
	}
	return (out);
}

#endif
