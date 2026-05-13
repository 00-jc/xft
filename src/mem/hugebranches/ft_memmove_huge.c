/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove_huge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:05:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/14 01:02:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memmove_512_tail(void *restrict dest,
	const void	*restrict const src, size_t n)
{
	t_u8		x[2];
	t_vu512a	interleaved[3];

	x[0] = -(1 < n) & 2;
	x[1] = -(0 < n) & 1;
	interleaved[2] = ((t_blk512r)src)[x[1]];
	interleaved[1] = ((t_blk512r)src)[x[0]];
	interleaved[0] = ((t_blk512r)src)[0];
	((t_blk512wa)dest)[x[1]] = interleaved[x[1]];
	((t_blk512wa)dest)[x[0]] = interleaved[x[0]];
	((t_blk512wa)dest)[0] = interleaved[0];
}

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memmove_512_huge(void *restrict dest,
	const void	*restrict const src, size_t n)
{
	t_vu512a	x[4];
	size_t		blkidx;
	void		*d;
	void		*s;

	d = ft_align_bkw((t_blk8w)dest + n, 64);
	s = (t_blk8w)src + n;
	*(t_blk512w)ft_overlap(dest, sizeof(t_vu512a), n) =
		*(t_blk512r)ft_overlap(src, sizeof(t_vu512a), n);
	n -= sizeof(t_vu512a);
	blkidx = n >> 6;
	while (blkidx >= 4)
	{
		x[0] = ((t_blk512r)s)[blkidx];
		x[1] = ((t_blk512r)s)[blkidx - 1];
		x[2] = ((t_blk512r)s)[blkidx - 2];
		x[3] = ((t_blk512r)s)[blkidx - 3];
		((t_blk512wa)d)[blkidx] = x[0];
		((t_blk512wa)d)[blkidx - 1] = x[1];
		((t_blk512wa)d)[blkidx - 2] = x[2];
		((t_blk512wa)d)[blkidx - 3] = x[3];
		blkidx -= 4;
	}
	ft_memmove_512_tail(d, s, blkidx);
}
