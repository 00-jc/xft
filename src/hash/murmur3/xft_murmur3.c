/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_murmur3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_hash.h"

#define DEFAULT_SEED	0x9e3779b185ebca87ULL

__attribute__((__always_inline__, __nonnull__(1, 2)))
static inline void	runblock0(t_u64a *s, t_u64a *restrict k)
{
	*k *= MURMUR_C1;
	*k = rotl(*k, 31) * MURMUR_C2;
	*s ^= *k;
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
static inline void	runblock1(t_u64a *s, t_u64a *restrict k)
{
	*k *= MURMUR_C2;
	*k = rotl(*k, 33) * MURMUR_C1;
	*s ^= *k;
}

__attribute__((pure, __nonnull__(1)))
t_u128a	xft_murmur3_with_seed(const t_u8 *restrict mem, t_u64a seed, t_size size)
{
	t_size	blk;
	t_u64a	s[2];
	t_u64a	k[2];

	blk = size >> 4;
	xft_bzero(k, sizeof(t_u64a) << 1);
	s[0] = seed;
	s[1] = seed;
	while (blk-- > 0)
	{
		*((t_blk128w)k) = *((t_blk128r)mem);
		runblock0(s, k);
		s[0] = (rotl(s[0], 27) + s[1]) * 5 + 0x52dce729;
		runblock1(&s[1], &k[1]);
		s[1] = (rotl(s[1], 27) + s[0]) * 5 + 0x38495ab5;
		mem += 16;
	}
	xft_murmur3_tail(mem, k, s, size & 15);
	s[0] ^= size;
	s[1] ^= size;
	s[0] += s[1];
	s[1] += s[0];
	s[0] = fmix64(s[0]);
	s[1] = fmix64(s[1]);
	return ((t_u128a)((s[1] << 1) + s[0]) << 64 | (s[0] + s[1]));
}

__attribute__((pure, __always_inline__, __nonnull__(1), __used__))
inline t_u128a	xft_murmur3(const t_u8 *restrict mem, t_size size)
{
	return (xft_murmur3_with_seed(mem, DEFAULT_SEED, size));
}
