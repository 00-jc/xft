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
# endif

#endif
