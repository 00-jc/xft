/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_murmur3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_hash.h"

#define DEFAULT_SEED	0x9e3779b185ebca87ULL 
#define C1				0x87c37b91114253d5ULL
#define C2				0x4cf5ad432745937f

__attribute__((__always_inline__, __nonnull__(1, 2)))
static inline void	runblock0(t_u64a *s, t_u64a *restrict k)
{
	*k *= C1;
	*k = rotl(*k, 31) * C2;
	*s ^= *k;
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
static inline void	runblock1(t_u64a *s, t_u64a *restrict k)
{
	*k *= C2;
	*k = rotl(*k, 33) * C1;
	*s ^= *k;
}

/* no safe duff's device since norminette forbids switches */

__attribute__((__always_inline__, __nonnull__(1, 2, 3)))
static inline void	ft_murmur3_tail(const t_u8 *restrict const tail,
		t_u64a k[2], t_u64a s[2], t_size len)
{
	t_size	i;

	k[0] = 0;
	k[1] = 0;
	i = 0;
	while (i < 7)
	{
		k[1] ^= ((len >= (15 - i)) & 1)
			* ((t_u64a)tail[14 - i] << (48 - (i << 3)));
		++i;
	}
	k[1] *= C2;
	k[1] = rotl(k[1], 33) * C1;
	s[1] ^= k[1] * ((len >= 9) & 1);
	i = 0;
	while (i < 8)
	{
		k[0] ^= ((len >= (8 - i)) & 1)
			* ((t_u64a)tail[7 - i] << (56 - (i << 3)));
		++i;
	}
	k[0] *= C1;
	k[0] = rotl(k[0], 31) * C2;
	s[0] ^= k[0] * ((len >= 1) & 1);
}

__attribute__((pure, __nonnull__(1)))
t_u128a	ft_murmur3_with_seed(const t_u8 *restrict mem, t_u64a seed, t_size size)
{
	t_size	blk;
	t_u64a	s[2];
	t_u64a	k[2];

	blk = size >> 4;
	ft_bzero(k, sizeof(t_u64a) << 1);
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
	ft_murmur3_tail(mem, k, s, size & 15);
	s[0] ^= size;
	s[1] ^= size;
	s[0] += s[1];
	s[1] += s[0];
	s[0] = fmix64(s[0]);
	s[1] = fmix64(s[1]);
	return ((t_u128a)((s[1] << 1) + s[0]) << 64 | (s[0] + s[1]));
}

__attribute__((pure, __always_inline__, __nonnull__(1)))
inline t_u128a	ft_murmur3(const t_u8 *restrict mem, t_size size)
{
	return (ft_murmur3_with_seed(mem, DEFAULT_SEED, size));
}
