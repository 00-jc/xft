/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_xxh3_medium_sizes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/22 13:25:59 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_xxh3.h>

__attribute__((pure, __always_inline__, __nonnull__(1, 2), __used__))
static inline t_u64a	xft_xxh3_mix16b(const t_u8 *input, const t_u8 *secret,
		t_u64a seed)
{
	t_u64a	lhs;
	t_u64a	rhs;

	__asm__ ("" : "+r"(seed));
	lhs = seed + *(t_blk64r)secret;
	rhs = (0 - seed) + *(t_blk64r)(secret + 8);
	lhs ^= *(t_blk64r)input;
	rhs ^= *(t_blk64r)(input + 8);
	return (xft_xxh3_mul128_fold64(lhs, rhs));
}

__attribute__((pure, __always_inline__, __used__))
inline t_u64a	xft_xxh3_len_17to128(t_buffer input,
	t_buffer secret, t_u64a seed)
{
	const t_size	n = input.size;
	t_u64a			acc;

	if (n < 17 || 128 < n || !input.mem || !secret.mem)
		__builtin_unreachable();
	acc = n * XXH3_PRIME64_1;
	if (n > 32)
	{
		if (n > 64)
		{
			if (n > 96)
				acc += xft_xxh3_mix16b(input.mem + 48, secret.mem + 96, seed)
					+ xft_xxh3_mix16b(input.mem + n - 64, secret.mem + 112,
						seed);
			acc += xft_xxh3_mix16b(input.mem + 32, secret.mem + 64, seed)
				+ xft_xxh3_mix16b(input.mem + n - 48, secret.mem + 80, seed);
		}
		acc += xft_xxh3_mix16b(input.mem + 16, secret.mem + 32, seed)
			+ xft_xxh3_mix16b(input.mem + n - 32, secret.mem + 48, seed);
	}
	acc += xft_xxh3_mix16b(input.mem, secret.mem, seed)
		+ xft_xxh3_mix16b(input.mem + n - 16, secret.mem + 16, seed);
	return (xft_xxh3_avalanche(acc));
}

__attribute__((pure, __always_inline__, __used__))
static inline t_u64a	xft_xxh3_len_129to240__first(t_buffer input,
	t_buffer secret, t_u64a seed, t_u64a acc)
{
	if (input.size < 129 || input.size > 240
		|| input.mem == nullptr || secret.mem == nullptr)
		__builtin_unreachable();
	acc += xft_xxh3_mix16b(input.mem + (0 << 4), secret.mem + (0 << 4), seed);
	acc += xft_xxh3_mix16b(input.mem + (1 << 4), secret.mem + (1 << 4), seed);
	acc += xft_xxh3_mix16b(input.mem + (2 << 4), secret.mem + (2 << 4), seed);
	acc += xft_xxh3_mix16b(input.mem + (3 << 4), secret.mem + (3 << 4), seed);
	acc += xft_xxh3_mix16b(input.mem + (4 << 4), secret.mem + (4 << 4), seed);
	acc += xft_xxh3_mix16b(input.mem + (5 << 4), secret.mem + (5 << 4), seed);
	acc += xft_xxh3_mix16b(input.mem + (6 << 4), secret.mem + (6 << 4), seed);
	acc += xft_xxh3_mix16b(input.mem + (7 << 4), secret.mem + (7 << 4), seed);
	return (xft_xxh3_avalanche(acc));
}

__attribute__((pure, __always_inline__, __used__))
inline t_u64a	xft_xxh3_len_129to240(t_buffer input,
	t_buffer secret, t_u64a seed)
{
	t_u64a	acc;
	t_size	nb_rounds;
	t_size	i;

	nb_rounds = input.size >> 4;
	if (!(input.size >= 129 && input.size <= 240)
		|| (input.mem == nullptr || secret.mem == nullptr)
		|| nb_rounds < 8)
		__builtin_unreachable();
	acc = input.size * XXH3_PRIME64_1;
	acc = xft_xxh3_len_129to240__first(input, secret, seed, acc);
	i = 8;
	while (i < nb_rounds)
	{
		acc += xft_xxh3_mix16b(input.mem + (i << 4),
				secret.mem + ((i - 8) << 4) + XXH3_MIDSIZE_STARTOFFSET, seed);
		++i;
		__asm__ ("" : "+r"(acc));
	}
	acc += xft_xxh3_mix16b(input.mem + input.size - 16,
			secret.mem + XXH3_SECRET_SIZE_MIN - XXH3_MIDSIZE_LASTOFFSET, seed);
	return (xft_xxh3_avalanche(acc));
}

__attribute__((pure, __always_inline__, __used__))
inline t_u64a	xft_xxh3_hash_short(t_buffer input, t_buffer secret,
	t_u64a seed)
{
	if (input.size < 129 || input.size > 240
		|| input.mem == nullptr || secret.mem == nullptr)
		__builtin_unreachable();
	if (input.size <= 16)
		return (xft_xxh3_len_0to16(input, secret, seed));
	else if (input.size <= 128)
		return (xft_xxh3_len_17to128(input, secret, seed));
	return (xft_xxh3_len_129to240(input, secret, seed));
}
