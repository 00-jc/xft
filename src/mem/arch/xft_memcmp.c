/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 13:02:17 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline t_ssize	xft_memcmp_short(t_cany restrict const ptr1,
	t_cany restrict const ptr2, t_size n)
{
	t_nmask		mask;
	t_nveca		load0;
	t_nveca		load1;

	mask = (t_nmask)(~(-1ULL << n));
	load0 = xft_vmask_load(ptr1, mask);
	load1 = xft_vmask_load(ptr2, mask);
	mask = xft_vmask((t_nvec)(load0 != load1));
	if (mask)
		return (load0[xft_memctz_u64(mask)] - load1[xft_memctz_u64(mask)]);
	return (0);
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline t_ssize	xft_memcmp_tail(t_cany restrict const ptr1,
	t_cany restrict const ptr2, t_size n)
{
	t_nmask		mask;
	t_nveca		load0;
	t_nveca		load1;
	t_size		diffbyte;

	if (n == 0)
		return (0);
	load0 = *(t_blknr)xft_overlap(ptr1, sizeof(t_nvec), n);
	load1 = *(t_blknr)xft_overlap(ptr2, sizeof(t_nvec), n);
	mask = xft_vmask((t_nvec)(load0 != load1))
		& xft_roll_mask(sizeof(t_nvec), n);
	if (mask)
	{
		diffbyte = xft_memctz_u64(mask);
		return (load0[diffbyte] - load1[diffbyte]);
	}
	return (0);
}

__attribute__((__nonnull__(1, 2)))
t_ssize	xft_memcmp(t_cany restrict const dest,
	t_cany restrict src, t_size n)
{
	t_nmask		mask;
	t_nveca		load0;
	t_nveca		load1;
	t_size		offst;
	t_size		diffb;

	if (n < sizeof(t_nvec))
		return (xft_memcmp_short(dest, src, n));
	offst = 0;
	while (n >= sizeof(t_nvec))
	{
		xft_prefetch0((t_blk8r)dest + offst, sizeof(t_nvec) << 1);
		xft_prefetch0((t_blk8r)src + offst, sizeof(t_nvec) << 1);
		load0 = *(t_blknr)((t_blk8r)dest + offst);
		load1 = *(t_blknr)((t_blk8r)src + offst);
		mask = xft_vmask((t_nvec)(load1 != load0));
		diffb = xft_memctz_u64(mask);
		if (mask)
			return (load0[diffb] - load1[diffb]);
		n -= sizeof(t_nvec);
		offst += sizeof(t_nvec);
	}
	return (xft_memcmp_tail((t_blk8r)dest + offst, (t_blk8r)src + offst, n));
}
