/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__ ((__nonnull__ (1), __always_inline__, pure, __used__))
inline t_any	xft__fix_last_w(const t_u8 *restrict const ptr,
	t_size n, t_u8 msk)
{
	t_vu128a		w;
	t_vu128			*adjusted;
	t_u16a			packed;
	t_uptr			p;

	if (n != 0)
	{
		adjusted = (t_vu128 *)xft_overlap((t_any)ptr, sizeof(t_vu128), n);
		w = (t_vu128a)(*(t_blk128r)adjusted == msk);
		packed = xft_bitpack128(w) & xft_roll_mask(sizeof(t_vu128a), n);
		p = (t_uptr)adjusted + xft_memctz_u16(packed);
		return ((t_any)(-((t_uptr)(packed != 0)) & p));
	}
	return (nullptr);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_any	xft_memchr_minimal(t_cany restrict const ptr,
	t_u8 c, t_size n)
{
	t_size	i;

	i = 0;
	while (i < n)
	{
		if (((t_blk8r)ptr)[i] == c)
			return ((t_any)((t_u8 *)ptr + i));
		++i;
	}
	return (nullptr);
}

__attribute__((__nonnull__ (1), __always_inline__, pure, __used__))
inline t_any	xft_memchr_128(t_cany restrict ptr, int c, t_size n)
{
	t_u16a						hasz;
	t_vu128a					w;
	const t_u8		*restrict	bp;
	t_vu128						*wptr;

	bp = (t_u8 *)ptr;
	wptr = (t_vu128a *)bp;
	while (n >= sizeof (t_vu128a))
	{
		xft_prefetch0(wptr, sizeof(t_vu128a) << 1);
		w = (t_vu128a)(*((t_blk128r)wptr) == (t_u8)c);
		hasz = xft_bitpack128(w);
		if (hasz)
			return ((void)(hasz = (t_u16a)xft_memctz_u16(hasz)),
			(t_any)((t_u8 *)wptr + hasz));
		wptr++;
		n -= sizeof (t_vu128);
	}
	return (xft__fix_last_w ((t_u8 *)wptr, n, (t_u8)c));
}
