/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 04:07:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__ ((__nonnull__ (1), __always_inline__, pure))
inline void	*ft__fix_last_w(const t_u8 *restrict const ptr,
	size_t n, t_u8 msk)
{
	t_vu128a		w;
	t_vu128			*adjusted;
	t_u16a			packed;
	t_uptr			p;

	if (n != 0)
	{
		adjusted = (t_vu128 *)ft_overlap((void *)ptr, sizeof(t_vu128), n);
		w = *(t_blk128r)adjusted == msk;
		packed = ft_bitpack128(w) & ft_roll_mask(sizeof(t_vu128a), n);
		p = (t_uptr)adjusted + ft_memctz_u16(packed);
		return ((void *)(-((t_uptr)(packed != 0)) & p));
	}
	return (nullptr);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	*ft_memchr_minimal(const void *restrict const ptr,
	t_u8 c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((t_blk8r)ptr)[i] == c)
			return ((void *)((t_u8 *)ptr + i));
		++i;
	}
	return (nullptr);
}

__attribute__((__nonnull__ (1), __always_inline__, pure))
inline void	*ft_memchr_sse(const void *restrict ptr, int c, size_t n)
{
	t_u16a						hasz;
	t_vu128a					w;
	const t_u8		*restrict	bp;
	t_vu128						*wptr;

	bp = (t_u8 *)ptr;
	wptr = (t_vu128a *)bp;
	while (n >= sizeof (t_vu128a))
	{
		ft_prefetch0(wptr, sizeof(t_vu128a) << 1);
		w = *((t_blk128r)wptr) == (t_u8)c;
		hasz = ft_bitpack128(w);
		if (hasz)
			return ((void)(hasz = (t_u16a)ft_memctz_u16(hasz)),
			(void *)((t_u8 *)wptr + hasz));
		wptr++;
		n -= sizeof (t_vu128);
	}
	return (ft__fix_last_w ((t_u8 *)wptr, n, (t_u8)c));
}
