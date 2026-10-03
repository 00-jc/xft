/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_murmur3_tail.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_hash.h"

__attribute__((__always_inline__, __nonnull__(1), __pure__, __used__))
inline t_u64a	xft_murmur3_tail_word(const t_u8 *restrict const tail,
		t_size len, t_size base, t_size n)
{
	t_u64a	k;
	t_size	i;
	t_size	g;

	k = 0;
	i = 0;
	while (i < n)
	{
		g = (len > (base + i)) & 1;
		k ^= g * ((t_u64a)tail[(base + i) * g] << (i << 3));
		++i;
	}
	return (k);
}

__attribute__((__always_inline__, __nonnull__(1, 2, 3), __used__))
inline void	xft_murmur3_tail(const t_u8 *restrict const tail,
		t_u64a k[2], t_u64a s[2], t_size len)
{
	k[0] = 0;
	k[1] = 0;
	if (__builtin_expect(len == 0, 0))
		return ;
	k[1] = xft_murmur3_tail_word(tail, len, 8, 7);
	k[1] *= MURMUR_C2;
	k[1] = rotl(k[1], 33) * MURMUR_C1;
	s[1] ^= k[1] * ((len >= 9) & 1);
	k[0] = xft_murmur3_tail_word(tail, len, 0, 8);
	k[0] *= MURMUR_C1;
	k[0] = rotl(k[0], 31) * MURMUR_C2;
	s[0] ^= k[0] * ((len >= 1) & 1);
}
