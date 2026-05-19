/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_xxh3.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 02:21:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/12 17:02:35 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_XXH3_H
# define FT_P_XXH3_H

# include "types.h"
# include "bmi.h"
# include "hash.h"
# include "private/ft_p_asm.h"
# include "private/ft_p_mem.h"
# include "hint.h"
# include <stdlib.h>

# define XXH3_STRIPE_LEN 			64
# define XXH3_SECRET_CONSUME_RATE 	8 
# define XXH3_ACC_NB 				8 
# define XXH3_MIDSIZE_MAX			240
# define XXH3_PRIME32_1				0x9E3779B1
# define XXH3_PRIME32_2				0x85EBCA77
# define XXH3_PRIME32_3				0xC2B2AE3D
# define XXH3_PRIME64_1				0x9E3779B185EBCA87
# define XXH3_PRIME64_2				0xC2B2AE3D27D4EB4F
# define XXH3_PRIME64_3				0x165667B19E3779F9
# define XXH3_PRIME64_4				0x85EBCA77C2B2AE63
# define XXH3_PRIME64_5				0x27D4EB2F165667C5
# define XXH3_PRIME_MX1				0x165667919E3779F9ULL
# define XXH3_PRIME_MX2				0x9FB21C651E98DF25ULL
# define XXH3_SECRET_DEF_SIZE		192
# define XXH3_MIDSIZE_MAX			240
# define XXH3_MIDSIZE_STARTOFFSET	3
# define XXH3_MIDSIZE_LASTOFFSET	17
# define XXH3_SECRET_SIZE_MIN		136
# define XXH3_SECRET_LASTACC_START  7
# define XXH3_SECRET_MERGEACCS_START	11
# ifdef __clang__
#  define XXH3_PREFETCH_DIST		320
# else
#  ifdef __AVX512__
#   define XXH3_PREFETCH_DIST		512
#  else
#   define XXH3_PREFETCH_DIST		384
#  endif
# endif

typedef __attribute__((__aligned__(64))) t_u64a	t_secret[24];

t_u64a		ft_xxh3_avalanche(t_u64 hash)\
				__attribute__((const));

t_u64a		ft_xxh64_avalanche(t_u64 hash)\
				__attribute__((const));

t_u64a		ft_xxh3_len0(t_buffer secret, t_u64 seed)\
				__attribute__((pure));

t_u64a		ft_xxh3_len_1to3(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		ft_xxh3_len_4to8(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		ft_xxh3_len_9to16(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		ft_xxh3_len_0to16(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		ft_xxh3_mul128_fold64(t_u64a a, t_u64a b)\
				__attribute__((const));

t_u64a		ft_xxh3_len_17to128(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		ft_xxh3_len_129to240(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		ft_xxh3_hash_short(t_buffer input, t_buffer secret, t_u64a seed)\
				__attribute__((pure));

t_u64a		ft_xxh3_hashlong_64b(t_buffer input, t_u64a seed);

t_u64a		ft_xxh3_merge_accs(t_blk64w acc, const t_u8 *secret, t_u64 start)\
				__attribute__((pure));

t_u64a		ft_xxh3_xorshift64(t_u64a x, int shift)\
				__attribute__((const));

t_u64a		ft_xxh3_rrmxmx(t_u64a a, t_u64a b)\
				__attribute__((const));

t_buffer	ft_xxh3_get_secret(void)\
				__attribute__((const));

void		ft_xxh3_init_custom_secret(void *custom_secret, t_u64a seed)\
				__attribute__((__nonnull__(1)));

#endif
