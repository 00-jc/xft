/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_xxh3.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_XXH3_H
# define XFT_P_XXH3_H

# include <xft/primitives.h>
# include <xft/hash.h>
# include <xft/xft_p_mem.h>
# include <xft/types/xft_p_xxh3_types.h>

t_u64a		xft_xxh3_avalanche(t_u64 hash)\
				__attribute__((const));

t_u64a		xft_xxh64_avalanche(t_u64 hash)\
				__attribute__((const));

t_u64a		xft_xxh3_len0(t_buffer secret, t_u64 seed)\
				__attribute__((pure));

t_u64a		xft_xxh3_len_1to3(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		xft_xxh3_len_4to8(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		xft_xxh3_len_9to16(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		xft_xxh3_len_0to16(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		xft_xxh3_mul128_fold64(t_u64a a, t_u64a b)\
				__attribute__((const));

t_u64a		xft_xxh3_len_17to128(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		xft_xxh3_len_129to240(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		xft_xxh3_hash_short(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		xft_xxh3_hashlong_64b(t_buffer input, t_u64a seed);

t_u64a		xft_xxh3_merge_accs(t_blk64w acc, const t_u8 *secret, t_u64 start)\
				__attribute__((pure));

t_u64a		xft_xxh3_xorshift64(t_u64a x, int shift)\
				__attribute__((const));

t_u64a		xft_xxh3_rrmxmx(t_u64a a, t_u64a b)\
				__attribute__((const));

t_buffer	xft_xxh3_get_secret(void)\
				__attribute__((const));

void		xft_xxh3_init_custom_secret(t_any custom_secret, t_u64a seed)\
				__attribute__((__nonnull__(1)));

#endif
