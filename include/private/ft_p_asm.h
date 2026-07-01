/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_asm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_ASM_H
# define FT_P_ASM_H

# include "primitives.h"

typedef t_u8 *__restrict__ const									t_blk8w;
typedef const t_u8 *__restrict__ const								t_blk8r;

# if defined(__AVX512F__)  || defined(__AVX512BW__)  || \
    defined(__AVX512DQ__) || defined(__AVX512CD__)  || \
    defined(__AVX512VL__) || defined(__AVX512IFMA__) || \
    defined(__AVX512VBMI__) || defined(__AVX512VBMI2__) || \
    defined(__AVX512VNNI__) || defined(__AVX512BITALG__) || \
    defined(__AVX512FP16__)

#  define FT_HAS_512_VEC 1
#  define FT_HAS_256_VEC 1
#  define FT_HAS_128_VEC 1

# elif defined(__AVX__)  || defined(__AVX2__) || \
      defined(__FMA__)  || defined(__FMA4__) || \
      defined(__XOP__)

#  define FT_HAS_512_VEC 0
#  define FT_HAS_256_VEC 1
#  define FT_HAS_128_VEC 1

# else

#  define FT_HAS_512_VEC 0
#  define FT_HAS_256_VEC 0
#  define FT_HAS_128_VEC 1

# endif

/*
 *  Misaligned
 */

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_u8\
																	t_vu128;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_u8\
																	t_vu256;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_u8\
																	t_vu512;

typedef t_u32 *__restrict__ const									t_blk32w;
typedef const t_u32 *__restrict__ const								t_blk32r;
typedef t_u64 *__restrict__ const									t_blk64w;
typedef const t_u64 *__restrict__ const								t_blk64r;
typedef t_vu128 *__restrict__ const									t_blk128w;
typedef const t_vu128 *__restrict__ const							t_blk128r;
typedef t_vu256 *__restrict__ const									t_blk256w;
typedef const t_vu256 *__restrict__ const							t_blk256r;
typedef t_vu512 *__restrict__ const									t_blk512w;
typedef const t_vu512 *__restrict__ const							t_blk512r;

/*
 *  Aligned
 */

typedef __attribute__((vector_size(16), aligned(16), __may_alias__)) t_u8\
																	t_vu128a;

typedef __attribute__((vector_size(32), aligned(32), __may_alias__)) t_u8\
																	t_vu256a;

typedef __attribute__((vector_size(64), aligned(64), __may_alias__)) t_u8\
																	t_vu512a;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_u64\
																	t_vu64_512;

typedef __attribute__((vector_size(64), aligned(64), __may_alias__)) t_u64\
																	t_vu64_512a;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_u16\
																	t_vu16_512;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_u32\
																	t_vu32_512;

typedef t_u32a *__restrict__ const									t_blk32wa;
typedef const t_u32a *__restrict__ const							t_blk32ra;
typedef t_u64a *__restrict__ const									t_blk64wa;
typedef const t_u64a *__restrict__ const							t_blk64ra;
typedef t_vu128a *__restrict__ const								t_blk128wa;
typedef const t_vu128a *__restrict__ const							t_blk128ra;
typedef t_vu256a *__restrict__ const								t_blk256wa;
typedef const t_vu256a *__restrict__ const							t_blk256ra;
typedef t_vu512a *__restrict__ const								t_blk512wa;
typedef const t_vu512a *__restrict__ const							t_blk512ra;

t_vu512			get_high512(void)\
					__attribute__((const));
t_vu512			get_lones512(void)\
					__attribute__((const));
t_vu512			get_z512(void)\
					__attribute__((const));
t_vu512			get_mask512(t_u8 x)\
					__attribute__((const));

t_vu256			get_high256(void)\
					__attribute__((const));
t_vu256			get_lones256(void)\
					__attribute__((const));
t_vu256			get_z256(void)\
					__attribute__((const));
t_vu256			get_mask256(t_u8 x)\
					__attribute__((const));

t_vu128			get_high128(void)\
					__attribute__((const));
t_vu128			get_lones128(void)\
					__attribute__((const));
t_vu128			get_z128(void)\
					__attribute__((const));
t_vu128			get_mask128(t_u8 x)\
					__attribute__((const));

t_u16a			ft_bitpack128(t_vu128a vec)\
					__attribute__((const));

#endif
