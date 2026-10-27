/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_masked_load.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:02:20 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 13:55:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/types/xft_p_vmanip_types.h>

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu256a	xft_vmask_load256(t_cany ptr, t_u32a mask)
{
	return ((t_vu256a)__builtin_ia32_loaddquqi256_mask(ptr,
			(t_vc256)xft_vsplat256(0), mask));
}

#elif XFT_HAS_256_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__))
static inline t_vu256	xft__vmask_load256_split(t_cany ptr, t_u32a mask)
{
	t_vu256a	buf[2];
	t_size		off;
	const t_u8	*base;

	off = (t_uptr)ptr & 31;
	base = (const t_u8 *)ptr - off;
	buf[0] = *(t_blk256ra)(base
			+ (-(xft_memctz_u32(mask) + off >= 32) & 32));
	buf[1] = *(t_blk256ra)(base
			+ (-(31 - xft_memclz_u32(mask) + off >= 32) & 32));
	return (*(t_blk256r)((const t_u8 *)buf + off));
}

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu256a	xft_vmask_load256(t_cany ptr, t_u32a mask)
{
	const t_vu256	bit = {1, 2, 4, 8, 16, 32, 64, -128,
		1, 2, 4, 8, 16, 32, 64, -128, 1, 2, 4, 8, 16, 32, 64, -128,
		1, 2, 4, 8, 16, 32, 64, -128};
	t_u32			b[4];
	t_vu256			bmask;
	t_vu256			v;

	if (__builtin_expect(mask == 0, 0))
		return ((t_vu256a){0});
	b[0] = (mask & 0xFF) * 0x01010101U;
	b[1] = (mask >> 8 & 0xFF) * 0x01010101U;
	b[2] = (mask >> 16 & 0xFF) * 0x01010101U;
	b[3] = (mask >> 24) * 0x01010101U;
	bmask = (t_vu256)(t_v8si){(int)b[0], (int)b[0], (int)b[1], (int)b[1],
		(int)b[2], (int)b[2], (int)b[3], (int)b[3]};
	bmask = (t_vu256)((bmask & bit) == bit);
	if (__builtin_expect(((t_uptr)ptr & 0xFFF) > 0xFE0, 0))
		v = xft__vmask_load256_split(ptr, mask);
	else
		v = *(t_blk256r)ptr;
	return ((t_vu256a)(v & bmask));
}

#endif
