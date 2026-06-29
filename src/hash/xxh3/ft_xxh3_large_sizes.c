/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xxh3_large_sizes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 04:21:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 11:11:11 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_xxh3.h"

#define MASK 0x00000000FFFFFFFF

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
inline void	ft_xxh3_accumulate_512(t_blk8r acc, t_blk8r input, t_blk8r secret)
{
	t_vu64_512	*xacc;
	t_vu64_512	rr[7];
	t_vu32_512	d32;

	xacc = (t_vu64_512 *)acc;
	if ((t_uptr)acc & 63 || XXH3_STRIPE_LEN != sizeof(t_vu512))
		__builtin_unreachable();
	{
		rr[0] = *(const t_vu64_512 * const restrict)input;
		rr[1] = *(const t_vu64_512 * const restrict)secret;
		rr[2] = rr[0] ^ rr[1];
		rr[3] = rr[2] >> 32;
		rr[4] = (rr[2] & MASK) * (rr[3] & MASK);
		d32 = (t_vu32_512)rr[0];
		rr[5] = (t_vu64_512)(t_vu32_512){
			d32[2], d32[3], d32[0], d32[1], d32[6], d32[7], d32[4], d32[5],
			d32[10], d32[11], d32[8], d32[9], d32[14], d32[15], d32[12], d32[13]
		};
		rr[6] = *xacc + rr[5];
		*xacc = rr[4] + rr[6];
	}
}

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_xxh3_scramble_acc_512(t_blk8r acc, t_blk8r secret)
{
	const t_vu64_512		prime = (t_vu64_512){1, 1, 1, 1, 1, 1, 1, 1}
		* XXH3_PRIME32_1;
	t_vu64_512				*xacc;
	t_vu64_512				rr[7];

	if ((t_uptr)acc & 63 || XXH3_STRIPE_LEN != sizeof(t_vu512))
		__builtin_unreachable();
	{
		xacc = (t_vu64_512 * const restrict)acc;
		rr[0] = *xacc;
		rr[1] = rr[0] >> 47;
		rr[2] = *(const t_vu64_512 * const restrict)secret;
		rr[3] = rr[2] ^ rr[0] ^ rr[1];
		rr[4] = rr[3] >> 32;
		rr[5] = (rr[3] & MASK) * (prime & MASK);
		rr[6] = (rr[4] & MASK) * (prime & MASK);
		*xacc = rr[5] + (rr[6] << 32);
	}
}

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
inline void	ft_xxh3_accumulate(t_blk8r accs,
	t_blk8r input, t_blk8r secret, t_size nb_stripes)
{
	t_size	n;
	void	*in;

	n = 0;
	while (n < nb_stripes)
	{
		in = (void *)(input + (n * XXH3_STRIPE_LEN));
		ft_prefetch0(in, XXH3_PREFETCH_DIST);
		ft_xxh3_accumulate_512(accs, in,
			secret + (n * XXH3_SECRET_CONSUME_RATE));
		++n;
	}
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_xxh3_hashlong_internal_loop(t_blk8r acc, t_buffer input,
		t_buffer secret)
{
	t_size	nb_str_blk;
	t_size	blen;
	t_size	nb_blks;
	t_size	nb_stripes;
	t_size	n;

	if (input.mem == nullptr || secret.mem == nullptr
		|| input.size < XXH3_STRIPE_LEN)
		__builtin_unreachable();
	nb_str_blk = (secret.size - XXH3_STRIPE_LEN) / XXH3_SECRET_CONSUME_RATE;
	blen = XXH3_STRIPE_LEN * nb_str_blk;
	nb_blks = (input.size - 1) / blen;
	n = 0;
	while (n < nb_blks)
	{
		ft_xxh3_accumulate(acc, input.mem + n * blen, secret.mem, nb_str_blk);
		ft_xxh3_scramble_acc_512(acc, secret.mem + secret.size
			- XXH3_STRIPE_LEN);
		++n;
	}
	nb_stripes = ((input.size - 1) - (blen * nb_blks)) / XXH3_STRIPE_LEN;
	ft_xxh3_accumulate(acc, input.mem + nb_blks * blen, secret.mem, nb_stripes);
	ft_xxh3_accumulate_512(acc, input.mem + input.size - XXH3_STRIPE_LEN,
		secret.mem + secret.size - XXH3_STRIPE_LEN - XXH3_SECRET_LASTACC_START);
}

t_u64a	ft_xxh3_hashlong_64b(t_buffer input, t_u64a seed)
{
	t_vu64_512a		acc;
	t_secret		custom_secret;
	t_buffer		secret;

	acc = (t_vu64_512a){
		XXH3_PRIME32_3, XXH3_PRIME64_1, XXH3_PRIME64_2, XXH3_PRIME64_3,
		XXH3_PRIME64_4, XXH3_PRIME32_2, XXH3_PRIME64_5, XXH3_PRIME32_1
	};
	ft_xxh3_init_custom_secret(custom_secret, seed);
	secret = (t_buffer){.mem = (t_u8 *)custom_secret,
		.size = XXH3_SECRET_DEF_SIZE};
	if (input.mem == nullptr || secret.mem == nullptr
		|| secret.size < sizeof(acc) + XXH3_SECRET_MERGEACCS_START)
		__builtin_unreachable();
	ft_xxh3_hashlong_internal_loop((t_blk8r) & acc, input, secret);
	return (ft_xxh3_merge_accs((t_u64 *) & acc,
			secret.mem + XXH3_SECRET_MERGEACCS_START,
			(t_u64)input.size * XXH3_PRIME64_1));
}
