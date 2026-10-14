/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 13:02:17 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__((__nonnull__(1), __always_inline__, pure, __used__))
inline t_any	xft_memchr_short(t_cany restrict const ptr, t_u8 c, t_size n)
{
	t_nmask	packed;
	t_uptr	p;

	packed = xft_veqmask(xft_vmask_load(ptr, (t_nmask)(~(-1ULL << n))), c)
		& (t_nmask)(~(-1ULL << n));
	p = (t_uptr)ptr + xft_memctz_u64(packed);
	return ((t_any)(-((t_uptr)(packed != 0)) & p));
}

__attribute__((__nonnull__(1), __always_inline__, pure, __used__))
inline t_any	xft_memchr_tail(t_cany restrict const ptr, t_u8 c, t_size n)
{
	t_cany	adjusted;
	t_nmask	packed;
	t_uptr	p;

	if (n == 0)
		return (nullptr);
	adjusted = xft_overlap(ptr, sizeof(t_nvec), n);
	packed = xft_veqmask(*(t_blknr)adjusted, c)
		& xft_roll_mask(sizeof(t_nvec), n);
	p = (t_uptr)adjusted + xft_memctz_u64(packed);
	return ((t_any)(-((t_uptr)(packed != 0)) & p));
}

__attribute__((__nonnull__(1), pure))
t_any	xft_memchr(t_cany restrict ptr, int c, t_size n)
{
	t_nmask			hasz;
	const t_nvec	*wptr;

	if (n < sizeof(t_nvec))
		return (xft_memchr_short(ptr, (t_u8)c, n));
	wptr = (const t_nvec *)ptr;
	while (n >= sizeof(t_nvec))
	{
		xft_prefetch_read0(wptr, sizeof(t_nvec) << 1);
		hasz = xft_veqmask(*wptr, (t_u8)c);
		if (hasz)
			return ((t_any)((const t_u8 *)wptr + xft_memctz_u64(hasz)));
		++wptr;
		n -= sizeof(t_nvec);
	}
	return (xft_memchr_tail(wptr, (t_u8)c, n));
}
