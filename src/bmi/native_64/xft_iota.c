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

#include <xft/types/xft_p_vmanip_types.h>

#if XFT_HAS_512_VEC

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec64a	xft_viota64(void)
{
	return (xft_viota512_64());
}

#elif XFT_HAS_256_VEC

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec64a	xft_viota64(void)
{
	return (xft_viota256_64());
}

#elif XFT_HAS_128_VEC

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec64a	xft_viota64(void)
{
	return (xft_viota128_64());
}

#else

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec64a	xft_viota64(void)
{
	t_nvec64a	out;
	t_size		i;

	i = 0;
	while (i < (XFT_NVEC_SIZE / 8))
	{
		out[i] = (t_u64)i;
		i++;
	}
	return (out);
}

#endif
