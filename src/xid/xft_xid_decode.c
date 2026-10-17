/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_xid_decode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 13:37:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 16:41:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xid.h"
#include "mem.h"

// branch? i hardly know her.

// this breaks the api consistence of xft_fatptr passing on purpose,
// we usually want to add to the pointer in a hot loop and not call
// a constructor every time.

// length from the lead byte in the low 8 bits, 0 for a continuation
// byte or an 0xF8..0xFF lead
__attribute__((const, __flatten__, __used__, __always_inline__))
inline t_u8	xft_xid_codepoint_len(t_u32a codepoint)
{
	t_u8		n;

	n = (t_u8)xft_tern((codepoint & 0x80) == 0, 1, 0);
	n = (t_u8)xft_tern((codepoint & 0xE0) == 0xC0, 2, n);
	n = (t_u8)xft_tern((codepoint & 0xF0) == 0xE0, 3, n);
	n = (t_u8)xft_tern((codepoint & 0xF8) == 0xF0, 4, n);
	return (n);
}

__attribute__((__hot__, pure, __always_inline__))
inline t_u32	xft_xid_decode(t_u32 w)
{
	const t_u32				min_cp[5] = {0, 0, 0x80, 0x800, 0x10000};
	t_u32a					n;
	t_u32a					ok;
	t_u32a					cp;

	n = (t_u32)xft_memclz_u32((~w << 24) | 0x800000);
	ok = (n - 2 <= 2) | !n;
	n += !n;
	n = (t_u32a)xft_tern(n > 4, 4, n);
	w &= ~0u >> ((4 - n) << 3);
	ok &= (w & 0xC0C0C000u) == (0x808080u >> ((4 - n) << 3) << 8);
	cp = (w & 0xFF & (0xFFu >> (n + (n > 1)))) << 18 | (w >> 8 & 0x3F) << 12
		| (w >> 16 & 0x3F) << 6 | (w >> 24 & 0x3F);
	cp >>= 6 * (4 - n);
	ok &= cp >= min_cp[n];
	ok &= (cp <= 0x10FFFF) & (cp - 0xD800 > 0x7FF);
	return (cp & -ok);
}

__attribute__((__nonnull__(1), pure, __always_inline__, __used__))
inline t_u32a	xft_xid_load_point(const t_u8 *__restrict__ const bytes,
	t_size cap)
{
	t_u32a		codepoint;

	codepoint = xft_mload_rel_u32(xft_fatptr(bytes, cap), 0);
	codepoint |= xft_mload_rel_u24(xft_fatptr(bytes, cap), 0);
	codepoint |= xft_mload_rel_u16(xft_fatptr(bytes, cap), 0);
	codepoint |= xft_mload_rel_u8(xft_fatptr(bytes, cap), 0);
	return (codepoint);
}
