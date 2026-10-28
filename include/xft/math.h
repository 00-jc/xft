/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include <xft/types/math_types.h>

t_f32			xft_q_sqrt(t_f32 x)\
					__attribute__((const));
t_f64			xft_q_dsqrt(t_f64 number)\
					__attribute__((const));
t_f32			xft_sqrt(t_f32 number)\
					__attribute__((const));
t_f64			xft_dsqrt(t_f64 number)\
					__attribute__((const));
t_f32			xft_q_sqrt_round(t_f32 number, t_u8 n)\
					__attribute__((const));
t_f32			xft_q_sqrt_fround(t_f32 number)\
					__attribute__((const));
t_f32			xft_roundf(t_f32 x, t_u8 n)\
					__attribute__((const));
t_f32			xft_floorf(t_f32 x)\
					__attribute__((const));
t_f32			xft_ceilf(t_f32 x)\
					__attribute__((const));

# ifdef __SIZEOF_INT128__

t_u128			xft_pow_u128(t_u128 x, t_u128 n)\
					__attribute__((const));

# endif

t_u64			xft_pow_u64(t_u64 x, t_u64 n)\
					__attribute__((const));
t_u32			xft_pow_u32(t_u32 x, t_u32 n)\
					__attribute__((const));
t_u8			xft_pow_u8(t_u8 x, t_u8 n)\
					__attribute__((const));
int				xft_ipow(int x, t_u64 n)\
					__attribute__((const));
long long		xft_lpow(long long x, t_u64 n)\
					__attribute__((const));
t_f32			xft_fpow(t_f32 x, t_u64 n)\
					__attribute__((const));
t_f64			xft_dpow(t_f64 x, t_u64 n)\
					__attribute__((const));
t_f32			xft_roundff(t_f32 x)\
					__attribute__((const));
t_f64			xft_fabs(t_f64 x)\
					__attribute__((const));
t_f32			xft_rsqrt(t_f32 number)\
					__attribute__((const));
t_f64			xft_drsqrt(t_f64 number)\
					__attribute__((const));
t_4packd		xft_drsqrt_x4(t_4packd d1)\
					__attribute__ ((const));

t_3dcoords		xft_3dsub(const t_3dcoords *__restrict__ const a,\
					const t_3dcoords *__restrict__ const b)\
					__attribute__((__nonnull__(1, 2), pure));
t_3dcoords		xft_3dadd(const t_3dcoords *__restrict__ const a,\
					const t_3dcoords *__restrict__ const b)\
					__attribute__((__nonnull__(1, 2), pure));
t_f64			xft_3dnorm(const t_3dcoords *__restrict__ const c)\
					__attribute__((__nonnull__(1), pure));
t_f64			xft_3ddot(const t_3dcoords *__restrict__ const a,\
					const t_3dcoords *__restrict__ const b)\
					__attribute__((__nonnull__(1, 2), pure));
t_3dcoords		xft_3dunit(const t_3dcoords *__restrict__ const c)\
					__attribute__((__nonnull__(1), pure));
t_3dcoords		xft_3dmul(const t_3dcoords *__restrict__ const a,\
					const t_3dcoords *__restrict__ const b)\
					__attribute__((__nonnull__(1, 2), pure));
t_3dcoords		xft_3ddiv(const t_3dcoords *__restrict__ const a,\
					const t_3dcoords *__restrict__ const b)\
					__attribute__((__nonnull__(1, 2), pure));
t_3dcoords		xft_3dcross(const t_3dcoords *__restrict__ const a,\
					const t_3dcoords *__restrict__ const b)\
					__attribute__((__nonnull__(1, 2), pure));
#endif
