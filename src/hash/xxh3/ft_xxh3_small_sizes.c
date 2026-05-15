/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xxh3_small_sizes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 02:40:31 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 11:12:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_xxh3.h"

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_len0(t_buffer secret, t_u64 seed)
{
	if (secret.mem == nullptr)
		__builtin_unreachable();
	seed ^= *(t_blk64r)(secret.mem + 56);
	seed ^= *(t_blk64r)(secret.mem + 64);
	return (ft_xxh64_avalanche(seed));
}

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_len_1to3(t_buffer input, t_buffer secret, t_u64a seed)
{
	t_u8	bytes[4];
	t_u64	extended;
	t_u64	bitflip;
	size_t	idx;

	if (input.size == 0 || input.size > 3
		|| input.mem == nullptr || secret.mem == nullptr)
		__builtin_unreachable();
	bytes[2] = input.mem[0];
	idx = input.size > 1;
	bytes[3] = input.mem[idx];
	bytes[0] = input.mem[input.size - 1];
	bytes[1] = (t_u8)input.size;
	extended = *(t_blk32r)bytes;
	bitflip = *(t_blk32r)secret.mem ^ *(t_blk32r)(secret.mem + 4);
	bitflip += seed;
	bitflip ^= extended;
	return (ft_xxh64_avalanche(bitflip));
}

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_len_4to8(t_buffer input, t_buffer secret, t_u64a seed)
{
	t_u32	input_hi;
	t_u32	input_lo;
	t_u64	input_64;
	t_u64	acc;

	if (input.size < 4 || input.size > 8
		|| input.mem == nullptr || secret.mem == nullptr)
		__builtin_unreachable();
	seed ^= (t_u64)ft_bswap32((t_u32)seed) << 32;
	input_hi = *(t_blk32r)input.mem;
	input_lo = *(t_blk32r)(input.mem + input.size - 4);
	acc = (*(t_blk64r)(secret.mem + 8) ^ *(t_blk64r)(secret.mem + 16)) - seed;
	input_64 = input_lo + ((t_u64)input_hi << 32);
	acc ^= input_64;
	return (ft_xxh3_rrmxmx(acc, input.size));
}

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_len_9to16(t_buffer input, t_buffer secret, t_u64a seed)
{
	t_u64	bitflip1;
	t_u64	bitflip2;
	t_u64	input_lo;
	t_u64	input_hi;
	t_u64	acc;

	if (input.size < 9 || input.size > 16
		|| input.mem == nullptr || secret.mem == nullptr)
		__builtin_unreachable();
	{
		bitflip1 = (*(t_blk64r)(secret.mem + 24) ^ *(t_blk64r)(secret.mem + 32))
			+ seed;
		bitflip2 = (*(t_blk64r)(secret.mem + 40) ^ *(t_blk64r)(secret.mem + 48))
			- seed;
		input_lo = *(t_blk64r)input.mem ^ bitflip1;
		input_hi = *(t_blk64r)(input.mem + input.size - 8) ^ bitflip2;
		acc = (t_u64)input.size + ft_bswap64(input_lo) + input_hi;
		acc += ft_xxh3_mul128_fold64(input_lo, input_hi);
		return (ft_xxh3_avalanche(acc));
	}
}

__attribute__((pure, __always_inline__))
inline t_u64a	ft_xxh3_len_0to16(t_buffer input, t_buffer secret, t_u64a seed)
{
	if (input.size > 16 || input.mem == nullptr || secret.mem == nullptr)
		__builtin_unreachable();
	if (input.size > 8)
		return (ft_xxh3_len_9to16(input, secret, seed));
	else if (input.size >= 4)
		return (ft_xxh3_len_4to8(input, secret, seed));
	else if (input.size > 0)
		return (ft_xxh3_len_1to3(input, secret, seed));
	return (ft_xxh3_len0(secret, seed));
}
