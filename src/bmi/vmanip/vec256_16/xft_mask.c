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
inline t_u16a	xft_vmask256_16(t_vu16_256 vec)
{
	return (__builtin_ia32_cvtw2mask256((t_vs16_256)vec));
}

#elif XFT_HAS_256_VEC

# if defined(__x86_64__)

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u16a	xft_vmask256_16(t_vu16_256 vec)
{
	t_u32a	r;

	r = (t_u32a)__builtin_ia32_pmovmskb256((t_vc256)
			__builtin_ia32_packsswb256((t_vs16_256)vec, (t_vs16_256)vec));
	return ((t_u16a)((r & 0xFF) | ((r >> 8) & 0xFF00)));
}

# endif

# if !defined(__x86_64__)

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u16a	xft_vmask256_16(t_vu16_256 vec)
{
	t_u16a	out;
	t_size	i;

	out = 0;
	i = 0;
	while (i < 16)
	{
		out |= (t_u16a)((vec[i] >> 15) & 1) << i;
		i++;
	}
	return (out);
}

# endif

#endif
