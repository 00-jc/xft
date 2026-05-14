/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove_huge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:05:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/14 07:29:26 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memmove_512_tail(void *restrict d,
	const void	*restrict s, size_t n2)
{
	size_t		x[2];
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

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
inline void	ft_memmove_512_cascade(void *restrict d,
	const void	*restrict const s, t_vu512a	x[4])
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

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memmove_512_huge(void *restrict dest,
	const void	*restrict const src, size_t n)
{
	t_vu512a	x[6];
	size_t		n2;
	void		*d;
	void		*s;

	d = ft_align_bkw((t_blk8w)dest + n, 63);
	s = (t_blk8w)src + ((t_uptr)d - (t_uptr)dest);
	x[4] = *(t_blk512r)ft_overlap(src, sizeof(t_vu512a), n);
	x[5] = *((t_blk512r)src);
	n2 = ((t_uptr)d - (t_uptr)dest) >> 6;
	while (4 <= n2)
	{
		n2 -= 4;
		s = (t_blk8w)s - (sizeof(t_vu512a) << 2);
		d = (t_blk8w)d - (sizeof(t_vu512a) << 2);
		ft_memmove_512_cascade(d, s, x);
	}
	ft_memmove_512_tail(d, s, n2);
	*(t_blk512w)ft_overlap(dest, sizeof(t_vu512a), n) = x[4];
	*((t_blk512w)dest) = x[5];
}
