/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memcmp_vec512.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline t_ssize	xft_memcmp_finalround(t_cany restrict const ptr1,
	t_cany restrict const ptr2, t_size offst, t_size n)
{
	t_u64a		mask;
	t_vu512a	load0;
	t_vu512a	load1;
	t_size		diffbyte;

	if (n == 0)
		return (0);
	offst <<= 6;
	load0 = *(t_blk512r)xft_overlap((t_blk8r)ptr1 + offst, sizeof(t_vu512a), n);
	load1 = *(t_blk512r)xft_overlap((t_blk8r)ptr2 + offst, sizeof(t_vu512a), n);
	mask = xft_bitpack512((t_vu512a)(load0 != load1))
		& xft_roll_mask(sizeof(t_vu512a), n);
	if (mask)
	{
		diffbyte = xft_memctz_u64(mask);
		return (load0[diffbyte] - load1[diffbyte]);
	}
	return (0);
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline t_ssize	xft_memcmp_512(t_cany restrict const ptr1,
	t_cany restrict const ptr2, t_size n)
{
	t_u64a		mask;
	t_vu512a	load0;
	t_vu512a	load1;
	t_size		offst;
	t_size		diffb;

	offst = 0;
	if (n < sizeof(t_vu512))
		return (xft_memcmp_minimal(ptr1, ptr2, offst, n));
	while (n >= sizeof(t_vu512))
	{
		xft_prefetch0(ptr1, sizeof(t_vu512a) << 1);
		xft_prefetch0(ptr2, sizeof(t_vu512a) << 1);
		load0 = ((t_blk512r)ptr1)[offst];
		load1 = ((t_blk512r)ptr2)[offst];
		mask = xft_bitpack512((t_vu512a)(load1 != load0));
		diffb = xft_memctz_u64(mask);
		if (mask)
			return (load0[diffb] - load1[diffb]);
		n -= sizeof(t_vu512a);
		++offst;
	}
	return (xft_memcmp_finalround(ptr1, ptr2, offst, n));
}

#endif
