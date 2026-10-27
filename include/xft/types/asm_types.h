/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/16 01:43:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_TYPES_H
# define ASM_TYPES_H

# include <xft/primitives.h>

typedef t_u8 *__restrict__ const									t_blk8w;
typedef const t_u8 *__restrict__ const								t_blk8r;

# if defined(__AVX512BW__) && defined(__AVX512VL__) && defined(__AVX512DQ__)

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

typedef t_u16 *__restrict__ const									t_blk16w;
typedef const t_u16 *__restrict__ const								t_blk16r;
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

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_u16\
																	t_vu16_128;

typedef __attribute__((vector_size(16), aligned(16), __may_alias__)) t_u16\
																	t_vu16_128a;

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_u32\
																	t_vu32_128;

typedef __attribute__((vector_size(16), aligned(16), __may_alias__)) t_u32\
																	t_vu32_128a;

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_u64\
																	t_vu64_128;

typedef __attribute__((vector_size(16), aligned(16), __may_alias__)) t_u64\
																	t_vu64_128a;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_u16\
																	t_vu16_256;

typedef __attribute__((vector_size(32), aligned(32), __may_alias__)) t_u16\
																	t_vu16_256a;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_u32\
																	t_vu32_256;

typedef __attribute__((vector_size(32), aligned(32), __may_alias__)) t_u32\
																	t_vu32_256a;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_u64\
																	t_vu64_256;

typedef __attribute__((vector_size(32), aligned(32), __may_alias__)) t_u64\
																	t_vu64_256a;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_u64\
																	t_vu64_512;

typedef __attribute__((vector_size(64), aligned(64), __may_alias__)) t_u64\
																	t_vu64_512a;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_u16\
																	t_vu16_512;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_u32\
																	t_vu32_512;

typedef __attribute__((vector_size(64), aligned(64), __may_alias__)) t_u16\
																	t_vu16_512a;

typedef __attribute__((vector_size(64), aligned(64), __may_alias__)) t_u32\
																	t_vu32_512a;

typedef t_u16a *__restrict__ const									t_blk16wa;
typedef const t_u16a *__restrict__ const							t_blk16ra;
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

typedef enum e_xft_nvec : t_u8
{
	XFT_NVEC_SIZE = 64,
}	t_xft_nvec;

typedef t_vu512														t_nvec;
typedef t_vu512a													t_nveca;
typedef t_u64a														t_nmask;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_u16\
																	t_nvec16;
typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_u32\
																	t_nvec32;
typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_u64\
																	t_nvec64;
typedef __attribute__((vector_size(64), aligned(64), __may_alias__)) t_u16\
																	t_nvec16a;
typedef __attribute__((vector_size(64), aligned(64), __may_alias__)) t_u32\
																	t_nvec32a;
typedef __attribute__((vector_size(64), aligned(64), __may_alias__)) t_u64\
																	t_nvec64a;
typedef t_u32a														t_nmask16;
typedef t_u16a														t_nmask32;
typedef t_u8														t_nmask64;

# elif XFT_HAS_256_VEC

typedef enum e_xft_nvec : t_u8
{
	XFT_NVEC_SIZE = 32,
}	t_xft_nvec;

typedef t_vu256														t_nvec;
typedef t_vu256a													t_nveca;
typedef t_u32a														t_nmask;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_u16\
																	t_nvec16;
typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_u32\
																	t_nvec32;
typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_u64\
																	t_nvec64;
typedef __attribute__((vector_size(32), aligned(32), __may_alias__)) t_u16\
																	t_nvec16a;
typedef __attribute__((vector_size(32), aligned(32), __may_alias__)) t_u32\
																	t_nvec32a;
typedef __attribute__((vector_size(32), aligned(32), __may_alias__)) t_u64\
																	t_nvec64a;
typedef t_u16a														t_nmask16;
typedef t_u8														t_nmask32;
typedef t_u8														t_nmask64;

# elif XFT_HAS_128_VEC

typedef enum e_xft_nvec : t_u8
{
	XFT_NVEC_SIZE = 16,
}	t_xft_nvec;

typedef t_vu128														t_nvec;
typedef t_vu128a													t_nveca;
typedef t_u16a														t_nmask;

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_u16\
																	t_nvec16;
typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_u32\
																	t_nvec32;
typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_u64\
																	t_nvec64;
typedef __attribute__((vector_size(16), aligned(16), __may_alias__)) t_u16\
																	t_nvec16a;
typedef __attribute__((vector_size(16), aligned(16), __may_alias__)) t_u32\
																	t_nvec32a;
typedef __attribute__((vector_size(16), aligned(16), __may_alias__)) t_u64\
																	t_nvec64a;
typedef t_u8														t_nmask16;
typedef t_u8														t_nmask32;
typedef t_u8														t_nmask64;

# else

typedef enum e_xft_nvec : t_u8
{
	XFT_NVEC_SIZE = 8,
}	t_xft_nvec;

typedef __attribute__((vector_size(8), aligned(1), __may_alias__)) t_u8\
																	t_nvec;

typedef __attribute__((vector_size(8), aligned(8), __may_alias__)) t_u8\
																	t_nveca;

typedef t_u8														t_nmask;

typedef __attribute__((vector_size(8), aligned(1), __may_alias__)) t_u16\
																	t_nvec16;
typedef __attribute__((vector_size(8), aligned(1), __may_alias__)) t_u32\
																	t_nvec32;
typedef __attribute__((vector_size(8), aligned(1), __may_alias__)) t_u64\
																	t_nvec64;
typedef __attribute__((vector_size(8), aligned(8), __may_alias__)) t_u16\
																	t_nvec16a;
typedef __attribute__((vector_size(8), aligned(8), __may_alias__)) t_u32\
																	t_nvec32a;
typedef __attribute__((vector_size(8), aligned(8), __may_alias__)) t_u64\
																	t_nvec64a;
typedef t_u8														t_nmask16;
typedef t_u8														t_nmask32;
typedef t_u8														t_nmask64;

# endif

typedef t_nvec *__restrict__ const									t_blknw;
typedef const t_nvec *__restrict__ const							t_blknr;
typedef t_nveca *__restrict__ const									t_blknwa;
typedef const t_nveca *__restrict__ const							t_blknra;

#endif
