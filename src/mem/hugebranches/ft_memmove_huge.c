/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove_huge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memmove_hugetail(t_any dest, t_cany const src, t_size n)
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
inline void	ft__hugekernel_fwd(t_any dest, t_cany const src,
	const t_size i, t_vu512a *const x)
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
inline void	ft_memmove_512_fwd(t_any dest, t_cany const src, t_size n)
{
	t_t_f64_size	s;
	t_size			delta;
	t_u8			*d;
	const t_u8		*sr;
	t_vu512a		x[5];

	delta = (-(t_uptr)dest) & 63;
	x[4] = *(t_blk512r)src;
	d = (t_u8 *)dest + delta;
	sr = (const t_u8 *)src + delta;
	n -= delta;
	s.blks = (n >> 6);
	s.i = 0;
	while (s.i + 4 <= s.blks)
	{
		ft__hugekernel_fwd(d, sr, s.i, x);
		s.i += 4;
	}
	s.i <<= 6;
	ft_memmove_hugetail(d + s.i, sr + s.i, n - s.i);
	*(t_blk512w)dest = x[4];
}

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memmove_512_tail(t_any d, t_cany s, t_size n2)
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

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
inline void	ft__hugekernel_move(t_any d, t_cany const s, t_vu512a x[4])
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
inline void	ft_memmove_512_huge(t_any dest, t_cany const src, t_size n)
{
	t_vu512a	x[6];
	t_size		n2;
	t_any		d;
	t_any		s;

	d = ft_align_bkw((t_blk8w)dest + n, 64);
	s = (t_blk8w)src + ((t_uptr)d - (t_uptr)dest);
	x[4] = *(t_blk512r)ft_overlap(src, sizeof(t_vu512a), n);
	x[5] = *((t_blk512r)src);
	n2 = ((t_uptr)d - (t_uptr)dest) >> 6;
	while (4 <= n2)
	{
		n2 -= 4;
		s = (t_blk8w)s - (sizeof(t_vu512a) << 2);
		d = (t_blk8w)d - (sizeof(t_vu512a) << 2);
		ft__hugekernel_move(d, s, x);
	}
	ft_memmove_512_tail(d, s, n2);
	*(t_blk512w)ft_overlap(dest, sizeof(t_vu512a), n) = x[4];
	*((t_blk512w)dest) = x[5];
}
