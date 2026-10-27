/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_xxh3_types.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_XXH3_TYPES_H
# define XFT_P_XXH3_TYPES_H

# include <xft/primitives.h>

typedef enum e_xxh3_size : t_u8
{
	XXH3_STRIPE_LEN = 64,
	XXH3_SECRET_CONSUME_RATE = 8,
	XXH3_ACC_NB = 8,
	XXH3_MIDSIZE_MAX = 240,
	XXH3_SECRET_DEF_SIZE = 192,
	XXH3_MIDSIZE_STARTOFFSET = 3,
	XXH3_MIDSIZE_LASTOFFSET = 17,
	XXH3_SECRET_SIZE_MIN = 136,
	XXH3_SECRET_LASTACC_START = 7,
	XXH3_SECRET_MERGEACCS_START = 11,
}	t_xxh3_size;

typedef enum e_xxh3_prime32 : t_u32
{
	XXH3_PRIME32_1 = 0x9E3779B1,
	XXH3_PRIME32_2 = 0x85EBCA77,
	XXH3_PRIME32_3 = 0xC2B2AE3D,
}	t_xxh3_prime32;

typedef enum e_xxh3_prime64 : t_u64
{
	XXH3_PRIME64_1 = 0x9E3779B185EBCA87,
	XXH3_PRIME64_2 = 0xC2B2AE3D27D4EB4F,
	XXH3_PRIME64_3 = 0x165667B19E3779F9,
	XXH3_PRIME64_4 = 0x85EBCA77C2B2AE63,
	XXH3_PRIME64_5 = 0x27D4EB2F165667C5,
	XXH3_PRIME_MX1 = 0x165667919E3779F9,
	XXH3_PRIME_MX2 = 0x9FB21C651E98DF25,
}	t_xxh3_prime64;

# ifdef __clang__

typedef enum e_xxh3_prefetch : t_u16
{
	XXH3_PREFETCH_DIST = 320,
}	t_xxh3_prefetch;

# else
#  ifdef __AVX512F__

typedef enum e_xxh3_prefetch : t_u16
{
	XXH3_PREFETCH_DIST = 512,
}	t_xxh3_prefetch;

#  else

typedef enum e_xxh3_prefetch : t_u16
{
	XXH3_PREFETCH_DIST = 384,
}	t_xxh3_prefetch;

#  endif
# endif

typedef __attribute__((__aligned__(64))) t_u64a	t_secret[24];

#endif
