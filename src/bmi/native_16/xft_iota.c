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
inline t_nvec16a	xft_viota16(void)
{
	return (xft_viota512_16());
}

#elif XFT_HAS_256_VEC

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec16a	xft_viota16(void)
{
	return (xft_viota256_16());
}

#elif XFT_HAS_128_VEC

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec16a	xft_viota16(void)
{
	return (xft_viota128_16());
}

#else

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec16a	xft_viota16(void)
{
	t_nvec16a	out;
	t_size		i;

	i = 0;
	while (i < (XFT_NVEC_SIZE / 2))
	{
		out[i] = (t_u16)i;
		i++;
	}
	return (out);
}

#endif
