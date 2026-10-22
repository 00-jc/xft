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

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__))
inline t_vu32_128a	xft_vmask_load128_32(t_cany ptr, t_u8 mask)
{
	return ((t_vu32_128a)__builtin_ia32_loaddqusi128_mask(ptr,
			(t_vs32_128){}, mask));
}

#elif XFT_HAS_256_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__))
inline t_vu32_128a	xft_vmask_load128_32(t_cany ptr, t_u8 mask)
{
	t_vs32_128	lanes;
	t_vs32_128	sel;

	lanes = (t_vs32_128)xft_vsplat128_32(mask);
	sel = (t_vs32_128)(xft_vsplat128_32(1) << xft_viota128_32());
	return ((t_vu32_128a)__builtin_ia32_maskloadd(ptr,
			(t_vs32_128)((lanes & sel) != 0)));
}

#elif XFT_HAS_128_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__))
inline t_vu32_128a	xft_vmask_load128_32(t_cany ptr, t_u8 mask)
{
	t_vu32_128a	out;
	t_size		i;
	t_size		lo;
	t_size		m;

	out = (t_vu32_128a){0};
	if (mask == 0)
		return (out);
	lo = xft_memctz_u32(mask);
	i = 0;
	while (i < 4)
	{
		m = -(t_size)((mask >> i) & 1);
		out[i] = (t_u32)(((const t_u32 *)ptr)[(i & m) | (lo & ~m)] & m);
		i++;
	}
	return (out);
}

#endif
