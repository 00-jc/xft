/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xxh3_medium_sizes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 03:16:31 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 23:03:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_xxh3.h"

__attribute__((pure, __always_inline__, __nonnull__(1, 2)))
inline t_u64a	ft_xxh3_mix16b(const t_u8 *input, const t_u8 *secret,
		t_u64a seed)
{
	t_u64a	lhs;
	t_u64a	rhs;

	__asm__ ("" : "+r"(seed));
	lhs = seed + *(t_blk64r)secret;
	rhs = (0 - seed) + *(t_blk64r)(secret + 8);
	lhs ^= *(t_blk64r)input;
	rhs ^= *(t_blk64r)(input + 8);
	return (ft_xxh3_mul128_fold64(lhs, rhs));
}

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_len_17to128(t_buffer input,
	t_buffer secret, t_u64a seed)
{
	t_u64a	acc;
	size_t	i;

	if (input.size < 17 || 128 < input.size || !input.mem
		|| !secret.mem)
		__builtin_unreachable();
	acc = input.size * XXH3_PRIME64_1;
	i = (input.size - 1) >> 5;
	while (1)
	{
		acc += ft_xxh3_mix16b(input.mem + (i << 4),
				secret.mem + (i << 5), seed);
		acc += ft_xxh3_mix16b(input.mem + input.size - ((i + 1) << 4),
				secret.mem + (i << 5) + 16, seed);
		if (i == 0)
			break ;
		--i;
	}
	return (ft_xxh3_avalanche(acc));
}

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_len_129to240__first(t_buffer input, t_buffer secret,
	t_u64a seed, t_u64a acc)
{
	if (input.size < 129 || input.size > 240
		|| input.mem == nullptr || secret.mem == nullptr)
		__builtin_unreachable();
	acc += ft_xxh3_mix16b(input.mem + (0 << 4), secret.mem + (0 << 4), seed);
	acc += ft_xxh3_mix16b(input.mem + (1 << 4), secret.mem + (1 << 4), seed);
	acc += ft_xxh3_mix16b(input.mem + (2 << 4), secret.mem + (2 << 4), seed);
	acc += ft_xxh3_mix16b(input.mem + (3 << 4), secret.mem + (3 << 4), seed);
	acc += ft_xxh3_mix16b(input.mem + (4 << 4), secret.mem + (4 << 4), seed);
	acc += ft_xxh3_mix16b(input.mem + (5 << 4), secret.mem + (5 << 4), seed);
	acc += ft_xxh3_mix16b(input.mem + (6 << 4), secret.mem + (6 << 4), seed);
	acc += ft_xxh3_mix16b(input.mem + (7 << 4), secret.mem + (7 << 4), seed);
	return (ft_xxh3_avalanche(acc));
}

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_len_129to240(t_buffer input,
	t_buffer secret, t_u64a seed)
{
	t_u64a	acc;
	size_t	nb_rounds;
	size_t	i;

	if (!(input.size >= 129 && input.size <= 240)
		|| (input.mem == nullptr || secret.mem == nullptr))
		__builtin_unreachable();
	acc = (t_u64)input.size * XXH3_PRIME64_1;
	acc = ft_xxh3_len_129to240__first(input, secret, seed, acc);
	nb_rounds = input.size >> 4;
	ft_pin_invariant(nb_rounds >= 8);
	i = 8;
	while (i < nb_rounds)
	{
		acc += ft_xxh3_mix16b(input.mem + (i << 4),
				secret.mem + ((i - 8) << 4) + XXH3_MIDSIZE_STARTOFFSET, seed);
		++i;
		__asm__ ("" : "+r"(acc));
	}
	acc += ft_xxh3_mix16b(input.mem + input.size - 16,
			secret.mem + XXH3_SECRET_SIZE_MIN - XXH3_MIDSIZE_LASTOFFSET, seed);
	return (ft_xxh3_avalanche(acc));
}

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_hash_short(t_buffer input, t_buffer secret, t_u64a seed)
{
	if (input.size < 129 || input.size > 240
		|| input.mem == nullptr || secret.mem == nullptr)
		__builtin_unreachable();
	if (input.size <= 16)
		return (ft_xxh3_len_0to16(input, secret, seed));
	else if (input.size <= 128)
		return (ft_xxh3_len_17to128(input, secret, seed));
	return (ft_xxh3_len_129to240(input, secret, seed));
}
