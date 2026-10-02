/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memchr_vec256.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

#if XFT_HAS_256_VEC

__attribute__ ((__nonnull__ (1), __always_inline__, pure, __used__))
inline t_any	xft__fix_last_w(const t_u8 *restrict const ptr,
	t_size n, t_u8 msk)
{
	t_vu256a		w;
	t_vu256			*adjusted;
	t_u32a			packed;
	t_uptr			p;

	if (n != 0)
	{
		adjusted = (t_vu256 *)xft_overlap((t_any)ptr, sizeof(t_vu256), n);
		w = (t_vu256a)(*(t_blk256r)adjusted == msk);
		packed = xft_bitpack256(w) & xft_roll_mask(sizeof(t_vu256a), n);
		p = (t_uptr)adjusted + xft_memctz_u32(packed);
		return ((t_any)(-((t_uptr)(packed != 0)) & p));
	}
	return (nullptr);
}

__attribute__((__nonnull__ (1), __always_inline__, pure, __used__))
inline t_any	xft_memchr_256(t_cany restrict ptr, int c, t_size n)
{
	t_u32a						hasz;
	t_vu256a					w;
	const t_u8		*restrict	bp;
	t_vu256						*wptr;

	bp = (t_u8 *)ptr;
	wptr = (t_vu256a *)bp;
	while (n >= sizeof (t_vu256a))
	{
		xft_prefetch0(wptr, sizeof(t_vu256) << 1);
		w = (t_vu256a)(*((t_blk256r)wptr) == (t_u8)c);
		hasz = xft_bitpack256(w);
		if (hasz)
			return ((void)(hasz = (t_u32a)xft_memctz_u32(hasz)),
			(t_any)((t_u8 *)wptr + hasz));
		wptr++;
		n -= sizeof (t_vu256);
	}
	return (xft__fix_last_w ((t_u8 *)wptr, n, (t_u8)c));
}

#endif
