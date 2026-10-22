/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_masked_load.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:02:20 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 17:39:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu128a	xft_vmask_load128(t_cany ptr, t_u16a mask)
{
	return ((t_vu128a)__builtin_ia32_loaddquqi128_mask(ptr,
			(t_vc128)xft_vsplat128(0), mask));
}

#elif XFT_HAS_128_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__))
static inline t_vu128	xft__vmask_load128_split(t_cany ptr, t_u16a mask)
{
	t_vu128a	buf[2];
	t_size		off;
	const t_u8	*base;

	off = (t_uptr)ptr & 15;
	base = (const t_u8 *)ptr - off;
	buf[0] = *(t_blk128ra)(base
			+ (-(xft_memctz_u16(mask) + off >= 16) & 16));
	buf[1] = *(t_blk128ra)(base
			+ (-(15 - xft_memclz_u16(mask) + off >= 16) & 16));
	return (*(t_blk128r)((const t_u8 *)buf + off));
}

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu128a	xft_vmask_load128(t_cany ptr, t_u16a mask)
{
	const t_vu128	bit = {1, 2, 4, 8, 16, 32, 64, -128,
		1, 2, 4, 8, 16, 32, 64, -128};
	t_u32			b[2];
	t_vu128			bmask;
	t_vu128			v;

	if (__builtin_expect(mask == 0, 0))
		return ((t_vu128a){0});
	b[0] = (mask & 0xFF) * 0x01010101U;
	b[1] = (mask >> 8) * 0x01010101U;
	bmask = (t_vu128)(t_v4si){(int)b[0], (int)b[0], (int)b[1], (int)b[1]};
	bmask = (t_vu128)((bmask & bit) == bit);
	if (__builtin_expect(((t_uptr)ptr & 0xFFF) > 0xFF0, 0))
		v = xft__vmask_load128_split(ptr, mask);
	else
		v = *(t_blk128r)ptr;
	return ((t_vu128a)(v & bmask));
}

#endif
