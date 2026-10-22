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
	__always_inline__, __flatten__, __used__))
inline t_nvec16a	xft_vmask_load16(t_cany ptr, t_nmask16 mask)
{
	return (xft_vmask_load512_16(ptr, mask));
}

#elif XFT_HAS_256_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_nvec16a	xft_vmask_load16(t_cany ptr, t_nmask16 mask)
{
	return (xft_vmask_load256_16(ptr, mask));
}

#elif XFT_HAS_128_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_nvec16a	xft_vmask_load16(t_cany ptr, t_nmask16 mask)
{
	return (xft_vmask_load128_16(ptr, mask));
}

#else

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_nvec16a	xft_vmask_load16(t_cany ptr, t_nmask16 mask)
{
	t_nvec16a	out;
	t_size		i;
	t_size		lo;
	t_size		m;

	out = (t_nvec16a){0};
	if (mask == 0)
		return (out);
	lo = xft_memctz_u32(mask);
	i = 0;
	while (i < (XFT_NVEC_SIZE / 2))
	{
		m = -(t_size)((mask >> i) & 1);
		out[i] = (t_u16)(((const t_u16 *)ptr)[(i & m) | (lo & ~m)] & m);
		i++;
	}
	return (out);
}

#endif
