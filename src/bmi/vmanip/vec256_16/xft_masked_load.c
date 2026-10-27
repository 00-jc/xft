/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_masked_load.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 12:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/types/xft_p_vmanip_types.h>

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu16_256a	xft_vmask_load256_16(t_cany ptr, t_u16a mask)
{
	return ((t_vu16_256a)__builtin_ia32_loaddquhi256_mask(ptr,
			(t_vs16_256){}, mask));
}

#elif XFT_HAS_256_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu16_256a	xft_vmask_load256_16(t_cany ptr, t_u16a mask)
{
	t_vu16_256a	out;
	t_size		i;
	t_size		lo;
	t_size		m;

	out = (t_vu16_256a){0};
	if (mask == 0)
		return (out);
	lo = xft_memctz_u32(mask);
	i = 0;
	while (i < 16)
	{
		m = -(t_size)((mask >> i) & 1);
		out[i] = (t_u16)(((const t_u16 *)ptr)[(i & m) | (lo & ~m)] & m);
		i++;
	}
	return (out);
}

#endif
