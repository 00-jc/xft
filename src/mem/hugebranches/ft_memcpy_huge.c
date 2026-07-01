/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_huge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memcpy_hugetail(void *restrict dest,
	const void	*restrict const src, t_size n)
{
	t_size		i[3];
	t_vu512a	x[4];

	if (__builtin_expect(63 < n, 1))
	{
		i[0] = -(128ULL < n) & 1;
		i[1] = -(192ULL < n) & 2;
		i[2] = -(256ULL < n) & 3;
		x[0] = ((t_blk512r)src)[0];
		x[1] = ((t_blk512r)src)[i[0]];
		x[2] = ((t_blk512r)src)[i[1]];
		x[3] = ((t_blk512r)src)[i[2]];
		((t_blk512wa)dest)[0] = x[0];
		((t_blk512wa)dest)[i[0]] = x[1];
		((t_blk512wa)dest)[i[1]] = x[2];
		((t_blk512wa)dest)[i[2]] = x[3];
	}
	if (__builtin_expect(n != 0, 1))
	{
		*((t_blk512w)ft_overlap(dest, sizeof(t_vu512a), n)) =
			*((t_blk512r)ft_overlap(src, sizeof(t_vu512a), n));
	}
}

__attribute__((__nonnull__(1, 2, 4), __always_inline__))
inline void	ft__huge_kernel_cpy(void *restrict dest,
	const void	*restrict const src, const t_size i,
	t_vu512a *restrict const x)
{
	x[0] = ((t_blk512r)src)[i + 0];
	x[1] = ((t_blk512r)src)[i + 1];
	x[2] = ((t_blk512r)src)[i + 2];
	x[3] = ((t_blk512r)src)[i + 3];
	((t_blk512wa)dest)[i + 0] = x[0];
	((t_blk512wa)dest)[i + 1] = x[1];
	((t_blk512wa)dest)[i + 2] = x[2];
	((t_blk512wa)dest)[i + 3] = x[3];
}

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memcpy_512_huge(void *restrict dest,
	const void	*restrict const src, t_size n)
{
	t_t_f64_size	s;
	t_size			delta;
	t_u8			*d;
	const t_u8		*sr;
	t_vu512a		x[4];

	delta = (-(t_uptr)dest) & 63;
	*(t_blk512w)dest = *(t_blk512r)src;
	d = (t_u8 *)dest + delta;
	sr = (const t_u8 *)src + delta;
	n -= delta;
	s.blks = (n >> 6);
	s.i = 0;
	while (s.i + 4 <= s.blks)
	{
		ft__huge_kernel_cpy(d, sr, s.i, x);
		s.i += 4;
	}
	s.i <<= 6;
	ft_memcpy_hugetail(d + s.i, sr + s.i, n - s.i);
}
