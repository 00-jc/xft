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
inline t_vu64_128a	xft_vmask_load128_64(t_cany ptr, t_u8 mask)
{
	return ((t_vu64_128a)__builtin_ia32_loaddqudi128_mask(ptr,
			(t_vs64_128){}, mask));
}

#elif XFT_HAS_256_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu64_128a	xft_vmask_load128_64(t_cany ptr, t_u8 mask)
{
	t_vs64_128	lanes;
	t_vs64_128	sel;

	lanes = (t_vs64_128)xft_vsplat128_64(mask);
	sel = (t_vs64_128)(xft_vsplat128_64(1) << xft_viota128_64());
	return ((t_vu64_128a)__builtin_ia32_maskloadq(ptr,
			(t_vs64_128)((lanes & sel) != 0)));
}

#elif XFT_HAS_128_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu64_128a	xft_vmask_load128_64(t_cany ptr, t_u8 mask)
{
	t_vu64_128a	out;
	t_size		i;
	t_size		lo;
	t_size		m;

	out = (t_vu64_128a){0};
	if (mask == 0)
		return (out);
	lo = xft_memctz_u32(mask);
	i = 0;
	while (i < 2)
	{
		m = -(t_size)((mask >> i) & 1);
		out[i] = (t_u64)(((const t_u64 *)ptr)[(i & m) | (lo & ~m)] & m);
		i++;
	}
	return (out);
}

#endif
