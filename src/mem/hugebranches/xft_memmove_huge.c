/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memmove_huge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/04 00:34:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_memmove_512_tail(t_any d, t_cany s, t_size n2)
{
	t_size		x[2];
	t_vu512a	interleaved[3];

	if (__builtin_expect(n2 != 0, 1))
	{
		d = (t_blk8w)d - (sizeof(t_vu512a) * n2);
		s = (t_blk8w)s - (sizeof(t_vu512a) * n2);
		x[0] = -(1 < n2) & 1;
		x[1] = -(2 < n2) & 2;
		interleaved[0] = ((t_blk512r)s)[0];
		interleaved[1] = ((t_blk512r)s)[x[0]];
		interleaved[2] = ((t_blk512r)s)[x[1]];
		((t_blk512wa)d)[0] = interleaved[0];
		((t_blk512wa)d)[x[0]] = interleaved[1];
		((t_blk512wa)d)[x[1]] = interleaved[2];
	}
}

__attribute__((__nonnull__(1, 2, 3), __always_inline__, __used__))
inline void	xft__hugekernel_move(t_any d, t_cany const s, t_vu512a x[4])
{
	x[0] = ((t_blk512r)s)[0];
	x[1] = ((t_blk512r)s)[1];
	x[2] = ((t_blk512r)s)[2];
	x[3] = ((t_blk512r)s)[3];
	((t_blk512wa)d)[0] = x[0];
	((t_blk512wa)d)[1] = x[1];
	((t_blk512wa)d)[2] = x[2];
	((t_blk512wa)d)[3] = x[3];
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_memmove_512_huge(t_any dest, t_cany const src, t_size n)
{
	t_vu512a	x[6];
	t_size		n2;
	t_any		d;
	t_any		s;

	d = xft_align_bkw((t_blk8w)dest + n, 64);
	s = (t_blk8w)src + ((t_uptr)d - (t_uptr)dest);
	x[4] = *(t_blk512r)xft_overlap(src, sizeof(t_vu512a), n);
	x[5] = *((t_blk512r)src);
	n2 = ((t_uptr)d - (t_uptr)dest) >> 6;
	while (4 <= n2)
	{
		n2 -= 4;
		s = (t_blk8w)s - (sizeof(t_vu512a) << 2);
		d = (t_blk8w)d - (sizeof(t_vu512a) << 2);
		xft__hugekernel_move(d, s, x);
	}
	xft_memmove_512_tail(d, s, n2);
	*(t_blk512w)xft_overlap(dest, sizeof(t_vu512a), n) = x[4];
	*((t_blk512w)dest) = x[5];
}
