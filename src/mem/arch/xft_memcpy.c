/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/04 00:30:11 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_memcpy_naive(t_any restrict dest,
	t_cany restrict const src, t_size n)
{
	t_u8 __attribute__	((uninitialized))	i[7];
	t_u8 __attribute__	((uninitialized))	s[7];

	i[0] = 0;
	i[1] = -(1ULL < n) & 1;
	i[2] = -(2ULL < n) & 2;
	i[3] = -(3ULL < n) & 3;
	i[4] = -(4ULL < n) & 4;
	i[5] = -(5ULL < n) & 5;
	i[6] = -(6ULL < n) & 6;
	s[0] = ((t_blk8r)src)[i[0]];
	s[1] = ((t_blk8r)src)[i[1]];
	s[2] = ((t_blk8r)src)[i[2]];
	s[3] = ((t_blk8r)src)[i[3]];
	s[4] = ((t_blk8r)src)[i[4]];
	s[5] = ((t_blk8r)src)[i[5]];
	s[6] = ((t_blk8r)src)[i[6]];
	((t_blk8w)dest)[i[0]] = s[0];
	((t_blk8w)dest)[i[1]] = s[1];
	((t_blk8w)dest)[i[2]] = s[2];
	((t_blk8w)dest)[i[3]] = s[3];
	((t_blk8w)dest)[i[4]] = s[4];
	((t_blk8w)dest)[i[5]] = s[5];
	((t_blk8w)dest)[i[6]] = s[6];
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_memmove_naive(t_any dest, t_cany const src, t_size n)
{
	t_u8 __attribute__	((uninitialized))	i[7];
	t_u8 __attribute__	((uninitialized))	s[7];

	i[0] = 0;
	i[1] = -(1ULL < n) & 1;
	i[2] = -(2ULL < n) & 2;
	i[3] = -(3ULL < n) & 3;
	i[4] = -(4ULL < n) & 4;
	i[5] = -(5ULL < n) & 5;
	i[6] = -(6ULL < n) & 6;
	s[0] = ((t_blk8r)src)[i[0]];
	s[1] = ((t_blk8r)src)[i[1]];
	s[2] = ((t_blk8r)src)[i[2]];
	s[3] = ((t_blk8r)src)[i[3]];
	s[4] = ((t_blk8r)src)[i[4]];
	s[5] = ((t_blk8r)src)[i[5]];
	s[6] = ((t_blk8r)src)[i[6]];
	((t_blk8w)dest)[i[0]] = s[0];
	((t_blk8w)dest)[i[1]] = s[1];
	((t_blk8w)dest)[i[2]] = s[2];
	((t_blk8w)dest)[i[3]] = s[3];
	((t_blk8w)dest)[i[4]] = s[4];
	((t_blk8w)dest)[i[5]] = s[5];
	((t_blk8w)dest)[i[6]] = s[6];
}

__attribute__((__nonnull__(1, 2), __hot__, __returns_nonnull__))
void	*xft_memcpy(t_any restrict dest,
	t_cany restrict const src, t_size n)
{
	if (__builtin_expect(dest == src || n == 0, 0))
		return (dest);
	else if (n < 8)
		xft_memcpy_naive(dest, src, n);
	else if (n < 16)
		xft_memcpy_64(dest, src, n);
	else if (n < 32)
		xft_memcpy_128(dest, src, n);
	else if (n < 64)
		xft_memcpy_256(dest, src, n);
	else if (n < 128)
		xft_memcpy_512(dest, src, n);
	else if (n < XFT_LLC_SIZE)
		xft_memcpy_512_huge(dest, src, n);
	else
		xft_memcpy_512_streaming(dest, src, n);
	return (dest);
}

#if !defined(XFT_REQUIRE_LIBC)

t_any	memcpy(t_any restrict dest, t_cany restrict const src, t_size n)\
			__attribute__((__nonnull__(1, 2), __hot__, __returns_nonnull__,\
				__weak__, __alias__("xft_memcpy")));

#endif
