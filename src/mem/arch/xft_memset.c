/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/04 00:30:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_memset_naive(t_any restrict dest,
	const t_u8 b, t_size n)
{
	t_u8 __attribute__	((uninitialized))	i[7];

	i[0] = 0;
	i[1] = -(1ULL < n) & 1;
	i[2] = -(2ULL < n) & 2;
	i[3] = -(3ULL < n) & 3;
	i[4] = -(4ULL < n) & 4;
	i[5] = -(5ULL < n) & 5;
	i[6] = -(6ULL < n) & 6;
	((t_blk8w)dest)[i[0]] = b;
	((t_blk8w)dest)[i[1]] = b;
	((t_blk8w)dest)[i[2]] = b;
	((t_blk8w)dest)[i[3]] = b;
	((t_blk8w)dest)[i[4]] = b;
	((t_blk8w)dest)[i[5]] = b;
	((t_blk8w)dest)[i[6]] = b;
}

__attribute__((__nonnull__(1), __hot__, __returns_nonnull__))
void	*xft_memset(t_any restrict dest,
	const t_i32 b, t_size n)
{
	if (__builtin_expect(n == 0, 0))
		return (dest);
	else if (n < 8)
		xft_memset_naive(dest, (t_u8)b, n);
	else if (n < 16)
		xft_memset_64(dest, (t_u8)b, n);
	else if (n < 32)
		xft_memset_128(dest, (t_u8)b, n);
	else if (n < 64)
		xft_memset_256(dest, (t_u8)b, n);
	else if (n < 128)
		xft_memset_512(dest, (t_u8)b, n);
	else if (n < XFT_LLC_SIZE)
		xft_memset_512_huge(dest, (t_u8)b, n);
	else
		xft_memset_512_streaming(dest, (t_u8)b, n);
	return (dest);
}

#if !defined(XFT_REQUIRE_LIBC)

t_any	memset(t_any restrict dest, const t_i32 b, t_size n)\
			__attribute__((__nonnull__(1), __hot__, __returns_nonnull__,\
				__weak__, __alias__("xft_memset")));

#endif
