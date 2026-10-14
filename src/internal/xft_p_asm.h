/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_asm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:07:33 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 19:47:40 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_ASM_H
# define XFT_P_ASM_H

# include "bmi.h"

typedef int		t_v4si __attribute__((__aligned__(1), __vector_size__(16)));
typedef int		t_v8si __attribute__((__aligned__(1), __vector_size__(32)));

# if XFT_HAS_512_VEC

t_vu512			xft_vsplat512(t_u8 b)\
					__attribute__((const));
t_u64a			xft_vmask512(t_vu512 vec)\
					__attribute__((const));
t_u64a			xft_veqmask512(t_vu512 vec, t_u8 b)\
					__attribute__((const));
t_u64a			xft_vtestmask512(t_vu512 vec, t_u8 b)\
					__attribute__((const));
t_u64a			xft_vrangemask512(t_vu512a v, t_u8 lo, t_u8 hi)\
					__attribute__((const));
t_vu512			xft_vcompress512(t_vu512a vec, t_u64a mask)\
					__attribute__((const));
t_vu512a		xft_vmask_load512(t_cany ptr, t_u64a mask)\
					__attribute__((__nonnull__(1), pure));
t_vu512a		xft_viota512(void) __attribute__((const));

t_vu16_512		xft_vsplat512_16(t_u16 b)\
					__attribute__((const));
t_u32a			xft_vmask512_16(t_vu16_512 vec)\
					__attribute__((const));
t_u32a			xft_veqmask512_16(t_vu16_512 vec, t_u16 b)\
					__attribute__((const));
t_u32a			xft_vtestmask512_16(t_vu16_512 vec, t_u16 b)\
					__attribute__((const));
t_u32a			xft_vrangemask512_16(t_vu16_512a v, t_u16 lo, t_u16 hi)\
					__attribute__((const));
t_vu16_512		xft_vcompress512_16(t_vu16_512a vec, t_u32a mask)\
					__attribute__((const));
t_vu16_512a		xft_vmask_load512_16(t_cany ptr, t_u32a mask)\
					__attribute__((__nonnull__(1), pure));
t_vu16_512a		xft_viota512_16(void) __attribute__((const));

t_vu32_512		xft_vsplat512_32(t_u32 b)\
					__attribute__((const));
t_u16a			xft_vmask512_32(t_vu32_512 vec)\
					__attribute__((const));
t_u16a			xft_veqmask512_32(t_vu32_512 vec, t_u32 b)\
					__attribute__((const));
t_u16a			xft_vtestmask512_32(t_vu32_512 vec, t_u32 b)\
					__attribute__((const));
t_u16a			xft_vrangemask512_32(t_vu32_512a v, t_u32 lo, t_u32 hi)\
					__attribute__((const));
t_vu32_512		xft_vcompress512_32(t_vu32_512a vec, t_u16a mask)\
					__attribute__((const));
t_vu32_512a		xft_vmask_load512_32(t_cany ptr, t_u16a mask)\
					__attribute__((__nonnull__(1), pure));
t_vu32_512a		xft_viota512_32(void) __attribute__((const));

t_vu64_512		xft_vsplat512_64(t_u64 b)\
					__attribute__((const));
t_u8			xft_vmask512_64(t_vu64_512 vec)\
					__attribute__((const));
t_u8			xft_veqmask512_64(t_vu64_512 vec, t_u64 b)\
					__attribute__((const));
t_u8			xft_vtestmask512_64(t_vu64_512 vec, t_u64 b)\
					__attribute__((const));
t_u8			xft_vrangemask512_64(t_vu64_512a v, t_u64 lo, t_u64 hi)\
					__attribute__((const));
t_vu64_512		xft_vcompress512_64(t_vu64_512a vec, t_u8 mask)\
					__attribute__((const));
t_vu64_512a		xft_vmask_load512_64(t_cany ptr, t_u8 mask)\
					__attribute__((__nonnull__(1), pure));
t_vu64_512a		xft_viota512_64(void) __attribute__((const));

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
t_u32a			xft_vrangemask256(t_vu256a v, t_u8 lo, t_u8 hi)\
					__attribute__((const));
t_vu256			xft_vcompress256(t_vu256a vec, t_u32a mask)\
					__attribute__((const));
t_vu256a		xft_vmask_load256(t_cany ptr, t_u32a mask)\
					__attribute__((__nonnull__(1), pure));
t_vu256a		xft_viota256(void) __attribute__((const));

t_vu16_256		xft_vsplat256_16(t_u16 b)\
					__attribute__((const));
t_u16a			xft_vmask256_16(t_vu16_256 vec)\
					__attribute__((const));
t_u16a			xft_veqmask256_16(t_vu16_256 vec, t_u16 b)\
					__attribute__((const));
t_u16a			xft_vtestmask256_16(t_vu16_256 vec, t_u16 b)\
					__attribute__((const));
t_u16a			xft_vrangemask256_16(t_vu16_256a v, t_u16 lo, t_u16 hi)\
					__attribute__((const));
t_vu16_256		xft_vcompress256_16(t_vu16_256a vec, t_u16a mask)\
					__attribute__((const));
t_vu16_256a		xft_vmask_load256_16(t_cany ptr, t_u16a mask)\
					__attribute__((__nonnull__(1), pure));
t_vu16_256a		xft_viota256_16(void) __attribute__((const));

t_vu32_256		xft_vsplat256_32(t_u32 b)\
					__attribute__((const));
t_u8			xft_vmask256_32(t_vu32_256 vec)\
					__attribute__((const));
t_u8			xft_veqmask256_32(t_vu32_256 vec, t_u32 b)\
					__attribute__((const));
t_u8			xft_vtestmask256_32(t_vu32_256 vec, t_u32 b)\
					__attribute__((const));
t_u8			xft_vrangemask256_32(t_vu32_256a v, t_u32 lo, t_u32 hi)\
					__attribute__((const));
t_vu32_256		xft_vcompress256_32(t_vu32_256a vec, t_u8 mask)\
					__attribute__((const));
t_vu32_256a		xft_vmask_load256_32(t_cany ptr, t_u8 mask)\
					__attribute__((__nonnull__(1), pure));
t_vu32_256a		xft_viota256_32(void) __attribute__((const));

t_vu64_256		xft_vsplat256_64(t_u64 b)\
					__attribute__((const));
t_u8			xft_vmask256_64(t_vu64_256 vec)\
					__attribute__((const));
t_u8			xft_veqmask256_64(t_vu64_256 vec, t_u64 b)\
					__attribute__((const));
t_u8			xft_vtestmask256_64(t_vu64_256 vec, t_u64 b)\
					__attribute__((const));
t_u8			xft_vrangemask256_64(t_vu64_256a v, t_u64 lo, t_u64 hi)\
					__attribute__((const));
t_vu64_256		xft_vcompress256_64(t_vu64_256a vec, t_u8 mask)\
					__attribute__((const));
t_vu64_256a		xft_vmask_load256_64(t_cany ptr, t_u8 mask)\
					__attribute__((__nonnull__(1), pure));
t_vu64_256a		xft_viota256_64(void) __attribute__((const));

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
t_u16a			xft_vrangemask128(t_vu128a v, t_u8 lo, t_u8 hi)\
					__attribute__((const));
t_vu128			xft_vcompress128(t_vu128a vec, t_u16a mask)\
					__attribute__((const));
t_vu128a		xft_vmask_load128(t_cany ptr, t_u16a mask)\
					__attribute__((__nonnull__(1), pure));
t_vu128a		xft_viota128(void) __attribute__((const));

t_vu16_128		xft_vsplat128_16(t_u16 b)\
					__attribute__((const));
t_u8			xft_vmask128_16(t_vu16_128 vec)\
					__attribute__((const));
t_u8			xft_veqmask128_16(t_vu16_128 vec, t_u16 b)\
					__attribute__((const));
t_u8			xft_vtestmask128_16(t_vu16_128 vec, t_u16 b)\
					__attribute__((const));
t_u8			xft_vrangemask128_16(t_vu16_128a v, t_u16 lo, t_u16 hi)\
					__attribute__((const));
t_vu16_128		xft_vcompress128_16(t_vu16_128a vec, t_u8 mask)\
					__attribute__((const));
t_vu16_128a		xft_vmask_load128_16(t_cany ptr, t_u8 mask)\
					__attribute__((__nonnull__(1), pure));
t_vu16_128a		xft_viota128_16(void) __attribute__((const));

t_vu32_128		xft_vsplat128_32(t_u32 b)\
					__attribute__((const));
t_u8			xft_vmask128_32(t_vu32_128 vec)\
					__attribute__((const));
t_u8			xft_veqmask128_32(t_vu32_128 vec, t_u32 b)\
					__attribute__((const));
t_u8			xft_vtestmask128_32(t_vu32_128 vec, t_u32 b)\
					__attribute__((const));
t_u8			xft_vrangemask128_32(t_vu32_128a v, t_u32 lo, t_u32 hi)\
					__attribute__((const));
t_vu32_128		xft_vcompress128_32(t_vu32_128a vec, t_u8 mask)\
					__attribute__((const));
t_vu32_128a		xft_vmask_load128_32(t_cany ptr, t_u8 mask)\
					__attribute__((__nonnull__(1), pure));
t_vu32_128a		xft_viota128_32(void) __attribute__((const));

t_vu64_128		xft_vsplat128_64(t_u64 b)\
					__attribute__((const));
t_u8			xft_vmask128_64(t_vu64_128 vec)\
					__attribute__((const));
t_u8			xft_veqmask128_64(t_vu64_128 vec, t_u64 b)\
					__attribute__((const));
t_u8			xft_vtestmask128_64(t_vu64_128 vec, t_u64 b)\
					__attribute__((const));
t_u8			xft_vrangemask128_64(t_vu64_128a v, t_u64 lo, t_u64 hi)\
					__attribute__((const));
t_vu64_128		xft_vcompress128_64(t_vu64_128a vec, t_u8 mask)\
					__attribute__((const));
t_vu64_128a		xft_vmask_load128_64(t_cany ptr, t_u8 mask)\
					__attribute__((__nonnull__(1), pure));
t_vu64_128a		xft_viota128_64(void) __attribute__((const));
# endif

#endif
