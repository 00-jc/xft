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
inline t_u8	xft_vmask128_16(t_vu16_128 vec)
{
	return (__builtin_ia32_cvtw2mask128((t_vs16_128)vec));
}

#elif XFT_HAS_128_VEC

# if defined(__x86_64__)

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u8	xft_vmask128_16(t_vu16_128 vec)
{
	return ((t_u8)__builtin_ia32_pmovmskb128((t_vc128)
			__builtin_ia32_packsswb128((t_vs16_128)vec, (t_vs16_128)vec)));
}

# endif

# if !defined(__x86_64__)

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u8	xft_vmask128_16(t_vu16_128 vec)
{
	t_u8	out;
	t_size	i;

	out = 0;
	i = 0;
	while (i < 8)
	{
		out |= (t_u8)((vec[i] >> 15) & 1) << i;
		i++;
	}
	return (out);
}

# endif

#endif
