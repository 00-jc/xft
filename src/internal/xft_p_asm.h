/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_asm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:07:33 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 12:34:49 by jaicastr         ###   ########.fr       */
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

# endif

t_nvec			xft_vsplat(t_u8 b)\
					__attribute__((const));
t_nmask			xft_vmask(t_nvec vec)\
					__attribute__((const));
t_nmask			xft_veqmask(t_nvec vec, t_u8 b)\
					__attribute__((const));
t_nmask			xft_vtestmask(t_nvec vec, t_u8 b)\
					__attribute__((const));
t_nmask			xft_vrangemask(t_nvec v, t_u8 lo, t_u8 hi)\
					__attribute__((const));

#endif
