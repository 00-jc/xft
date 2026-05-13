/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr_avx256.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:59:18 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

#if defined(__AVX2__)

__attribute__ ((__nonnull__ (1), __always_inline__, pure))
inline void	*ft__fix_last_w(const t_u8 *restrict const ptr,
	size_t n, t_u8 msk)
{
	t_vu256a		w;
	t_vu256			*adjusted;
	t_u32a			packed;
	t_uptr			p;

	if (n != 0)
	{
		adjusted = (t_vu256 *)ft_overlap((void *)ptr, sizeof(t_vu256), n);
		w = *(t_blk256r)adjusted == msk;
		packed = ft_bitpack256(w) & ft_roll_mask(sizeof(t_vu256a), n);
		p = (t_uptr)adjusted + ft_memctz_u32(packed);
		return ((void *)(-((t_uptr)(packed != 0)) & p));
	}
	return (nullptr);
}

__attribute__((__nonnull__ (1), __always_inline__, pure))
inline void	*ft_memchr_avx256(const void *restrict ptr, int c, size_t n)
{
	t_u32a						hasz;
	t_vu256a					w;
	const t_u8		*restrict	bp;
	t_vu256						*wptr;

	bp = (t_u8 *)ptr;
	wptr = (t_vu256a *)bp;
	while (n >= sizeof (t_vu256a))
	{
		ft_prefetch0(wptr, sizeof(t_vu256) << 1);
		w = *((t_blk256r)wptr) == (t_u8)c;
		hasz = ft_bitpack256(w);
		if (hasz)
			return ((void)(hasz = (t_u32a)ft_memctz_u32(hasz)),
			(void *)((t_u8 *)wptr + hasz));
		wptr++;
		n -= sizeof (t_vu256);
	}
	return (ft__fix_last_w ((t_u8 *)wptr, n, (t_u8)c));
}

#endif
