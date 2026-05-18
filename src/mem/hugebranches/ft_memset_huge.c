/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_huge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:05:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/18 21:29:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_memset_hugetail(void *restrict dest,
	const t_u8 c, size_t n)
{
	size_t				i[3];
	register t_vu512a	x;

	x = (t_vu512a){c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c};
	if (__builtin_expect(63 < n, 1))
	{
		i[0] = -(128ULL < n) & 1;
		i[1] = -(192ULL < n) & 2;
		i[2] = -(256ULL < n) & 3;
		((t_blk512wa)dest)[0] = x;
		((t_blk512wa)dest)[i[0]] = x;
		((t_blk512wa)dest)[i[1]] = x;
		((t_blk512wa)dest)[i[2]] = x;
	}
	if (__builtin_expect(n != 0, 1))
		*((t_blk512w)ft_overlap(dest, sizeof(t_vu512a), n)) = x;
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_memset_512_huge(void *restrict dest,
	const t_u8 c, size_t n)
{
	t_t_f64_size			s;
	size_t					delta;
	t_u8					*d;
	register t_vu512a		x;

	x = (t_vu512a){c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c,
		c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c};
	delta = (-(t_uptr)dest) & 63;
	*(t_blk512w)dest = x;
	d = (t_u8 *)dest + delta;
	n -= delta;
	s.blks = (n >> 6);
	s.i = 0;
	while (s.i + 4 <= s.blks)
	{
		((t_blk512wa)d)[s.i + 0] = x;
		((t_blk512wa)d)[s.i + 1] = x;
		((t_blk512wa)d)[s.i + 2] = x;
		((t_blk512wa)d)[s.i + 3] = x;
		s.i += 4;
	}
	s.i <<= 6;
	ft_memset_hugetail(d + s.i, c, n - s.i);
}
