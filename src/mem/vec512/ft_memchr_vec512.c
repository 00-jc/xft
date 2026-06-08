/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr_avx512.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:59:18 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 01:49:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

#if FT_HAS_512_VEC

__attribute__ ((__nonnull__ (1), __always_inline__, pure))
inline void	*ft__fix_last_w(const t_u8 *restrict const ptr,
	size_t n, t_u8 msk)
{
	t_vu512a		w;
	t_vu512			*adjusted;
	t_u64a			packed;
	t_uptr			p;

	if (n != 0)
	{
		adjusted = (t_vu512 *)ft_overlap((void *)ptr, sizeof(t_vu512), n);
		w = (t_vu512a)(*(t_blk512r)adjusted == msk);
		packed = ft_bitpack512(w) & ft_roll_mask(sizeof(t_vu512a), n);
		p = (t_uptr)adjusted + ft_memctz_u64(packed);
		return ((void *)(-((t_uptr)(packed != 0)) & p));
	}
	return (nullptr);
}

__attribute__((__nonnull__ (1), __always_inline__, pure))
inline void	*ft_memchr_avx512(const void *restrict ptr, int c, size_t n)
{
	t_u64a						hasz;
	t_vu512a					w;
	const t_u8		*restrict	bp;
	t_vu512						*wptr;

	bp = (t_u8 *)ptr;
	wptr = (t_vu512a *)bp;
	while (n >= sizeof (t_vu512a))
	{
		ft_prefetch0(wptr, sizeof(t_vu512a) << 1);
		w = (t_vu512a)(*((t_blk512r)wptr) == (t_u8)c);
		hasz = ft_bitpack512(w);
		if (hasz)
			return ((void)(hasz = ft_memctz_u64(hasz)),
			(void *)((t_u8 *)wptr + hasz));
		wptr++;
		n -= sizeof (t_vu512);
	}
	return (ft__fix_last_w ((t_u8 *)wptr, n, (t_u8)c));
}

#endif
