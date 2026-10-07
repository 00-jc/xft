/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memchr_vec512.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

#if XFT_HAS_512_VEC

__attribute__ ((__nonnull__ (1), __always_inline__, pure, __used__))
inline t_any	xft__fix_last_w(const t_u8 *restrict const ptr,
	t_size n, t_u8 msk)
{
	t_vu512a		w;
	t_vu512			*adjusted;
	t_u64a			packed;
	t_uptr			p;

	if (n != 0)
	{
		adjusted = (t_vu512 *)xft_overlap((t_any)ptr, sizeof(t_vu512), n);
		w = (t_vu512a)(*(t_blk512r)adjusted == msk);
		packed = xft_vmask512(w) & xft_roll_mask(sizeof(t_vu512a), n);
		p = (t_uptr)adjusted + xft_memctz_u64(packed);
		return ((t_any)(-((t_uptr)(packed != 0)) & p));
	}
	return (nullptr);
}

__attribute__((__nonnull__ (1), __always_inline__, pure, __used__))
inline t_any	xft_memchr_512(t_cany restrict ptr, int c, t_size n)
{
	t_u64a						hasz;
	t_vu512a					w;
	const t_u8		*restrict	bp;
	t_vu512						*wptr;

	bp = (t_u8 *)ptr;
	wptr = (t_vu512a *)bp;
	while (n >= sizeof (t_vu512a))
	{
		xft_prefetch0(wptr, sizeof(t_vu512a) << 1);
		w = (t_vu512a)(*((t_blk512r)wptr) == (t_u8)c);
		hasz = xft_vmask512(w);
		if (hasz)
			return ((void)(hasz = xft_memctz_u64(hasz)),
			(t_any)((t_u8 *)wptr + hasz));
		wptr++;
		n -= sizeof (t_vu512);
	}
	return (xft__fix_last_w ((t_u8 *)wptr, n, (t_u8)c));
}

#endif
