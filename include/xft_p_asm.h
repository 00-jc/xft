/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_asm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/07 12:10:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_ASM_H
# define XFT_P_ASM_H

# include "primitives.h"

typedef t_u8 *__restrict__ const									t_blk8w;
typedef const t_u8 *__restrict__ const								t_blk8r;

# if defined(__AVX512BW__)

#  define XFT_HAS_512_VEC 1
#  define XFT_HAS_256_VEC 1
#  define XFT_HAS_128_VEC 1

# elif defined(__AVX2__)

#  define XFT_HAS_512_VEC 0
#  define XFT_HAS_256_VEC 1
#  define XFT_HAS_128_VEC 1

# elif defined(__SSE2__) || defined(__ARM_NEON)

#  define XFT_HAS_512_VEC 0
#  define XFT_HAS_256_VEC 0
#  define XFT_HAS_128_VEC 1

# else

#  define XFT_HAS_512_VEC 0
#  define XFT_HAS_256_VEC 0
#  define XFT_HAS_128_VEC 0

# endif

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

# if XFT_HAS_512_VEC

t_vu512			xft_vsplat512(t_u8 b)\
					__attribute__((const));
t_u64a			xft_vmask512(t_vu512 vec)\
					__attribute__((const));
t_u64a			xft_veqmask512(t_vu512 vec, t_u8 b)\
					__attribute__((const));
t_u64a			xft_vtestmask512(t_vu512 vec, t_u8 b)\
					__attribute__((const));
t_u64a			xft_rangemask512(t_vu512a v, t_u8 lo, t_u8 hi)\
					__attribute__((const));

# endif

# if XFT_HAS_256_VEC

t_vu256			xft_vsplat256(t_u8 b)\
					__attribute__((const));
t_u32a			xft_vmask256(t_vu256 vec)\
					__attribute__((const));
t_u32a			xft_veqmask256(t_vu256 vec, t_u8 b)\
					__attribute__((const));
t_u32a			xft_vtestmask256(t_vu256 vec, t_u8 b)\
					__attribute__((const));
t_u32a			xft_rangemask256(t_vu256a v, t_u8 lo, t_u8 hi)\
					__attribute__((const));

# endif

# if XFT_HAS_128_VEC

t_vu128			xft_vsplat128(t_u8 b)\
					__attribute__((const));
t_u16a			xft_vmask128(t_vu128 vec)\
					__attribute__((const));
t_u16a			xft_veqmask128(t_vu128 vec, t_u8 b)\
					__attribute__((const));
t_u16a			xft_vtestmask128(t_vu128 vec, t_u8 b)\
					__attribute__((const));
t_u16a			xft_rangemask128(t_vu128a v, t_u8 lo, t_u8 hi)\
					__attribute__((const));

# endif

#endif
