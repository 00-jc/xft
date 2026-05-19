/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# ifdef __cplusplus

extern "C"
{

# endif

# include "mem.h"

typedef union u_fp
{
	t_f32	f;
	t_u32	i;
}	t_fp;

typedef union u_dp
{
	t_f64	f;
	t_u64	i;
}	t_dp;

typedef struct s_2packd
{
	t_f64	x;
	t_f64	y;
} __attribute__((aligned(16)))	t_2packd;

typedef struct s_4packd
{
	t_f64	x;
	t_f64	y;
	t_f64	z;
	t_f64	w;
} __attribute__((aligned(32)))	t_4packd;

typedef struct s_8packd
{
	t_f64	x;
	t_f64	y;
	t_f64	z;
	t_f64	w;
	t_f64	a;
	t_f64	b;
	t_f64	c;
	t_f64	d;
} __attribute__((aligned(64)))	t_8packd;

typedef t_4packd	t_3dcoords;

typedef struct s_3dcoordsx8
{
	t_3dcoords	a;
	t_3dcoords	b;
	t_3dcoords	c;
	t_3dcoords	d;
	t_3dcoords	e;
	t_3dcoords	f;
	t_3dcoords	g;
	t_3dcoords	h;
} __attribute__((aligned(64)))	t_3dcoordsx8;

t_f32			ft_q_sqrt(t_f32 x)\
					__attribute__((const));
t_f64			ft_q_dsqrt(t_f64 number)\
					__attribute__((const));
t_f32			ft_sqrt(t_f32 number)\
					__attribute__((const));
t_f64			ft_dsqrt(t_f64 number)\
					__attribute__((const));
t_f32			ft_q_sqrt_round(t_f32 number, t_u8 n)\
					__attribute__((const));
t_f32			ft_q_sqrt_fround(t_f32 number)\
					__attribute__((const));
t_f32			ft_roundf(t_f32 x, t_u8 n)\
					__attribute__((const));
t_f32			ft_floorf(t_f32 x)\
					__attribute__((const));
t_f32			ft_ceilf(t_f32 x)\
					__attribute__((const));
t_u128			ft_pow_u128(t_u128 x, t_u128 n)\
					__attribute__((const));
t_u64			ft_pow_u64(t_u64 x, t_u64 n)\
					__attribute__((const));
t_u32			ft_pow_u32(t_u32 x, t_u32 n)\
					__attribute__((const));
t_u8			ft_pow_u8(t_u8 x, t_u8 n)\
					__attribute__((const));
int				ft_ipow(int x, t_u64 n)\
					__attribute__((const));
long long		ft_lpow(long long x, t_u64 n)\
					__attribute__((const));
t_f32			ft_fpow(t_f32 x, t_u64 n)\
					__attribute__((const));
t_f64			ft_dpow(t_f64 x, t_u64 n)\
					__attribute__((const));
t_f32			ft_roundff(t_f32 x)\
					__attribute__((const));
t_f64			ft_fabs(t_f64 x)\
					__attribute__((const));
t_f32			ft_rsqrt(t_f32 number)\
					__attribute__((const));
t_f64			ft_drsqrt(t_f64 number)\
					__attribute__((const));
t_8packd		ft_drsqrt_x8(t_8packd d1)\
					__attribute__ ((const));
t_4packd		ft_drsqrt_x4(t_4packd d1)\
					__attribute__ ((const));
t_8packd		ft_dsqrt_x8(t_8packd d1)\
					__attribute__ ((const));
t_3dcoords		ft_3dsub(t_3dcoords a, t_3dcoords b)\
					__attribute__((const));
t_3dcoords		ft_3dadd(t_3dcoords a, t_3dcoords b)\
					__attribute__((const));
t_f64			ft_3dnorm(t_3dcoords c)\
					__attribute__((const));
t_f64			ft_3ddot(t_3dcoords a, t_3dcoords b)\
					__attribute__((const));
t_3dcoords		ft_3dunit(t_3dcoords c)\
					__attribute__((const));
t_3dcoords		ft_3dmul(t_3dcoords a, t_3dcoords b)\
					__attribute__((const));
t_3dcoords		ft_3ddiv(t_3dcoords a, t_3dcoords b)\
					__attribute__((const));
t_3dcoords		ft_3dcross(t_3dcoords a, t_3dcoords b)\
					__attribute__((const));
t_3dcoordsx8	ft_3dadd8(t_3dcoordsx8 a, t_3dcoordsx8 b)\
					__attribute__((const));
t_3dcoordsx8	ft_3dsub8(t_3dcoordsx8 a, t_3dcoordsx8 b)\
					__attribute__((const));
t_3dcoordsx8	ft_3dmul8(t_3dcoordsx8 a, t_3dcoordsx8 b)\
					__attribute__((const));
t_3dcoordsx8	ft_3ddiv8(t_3dcoordsx8 a, t_3dcoordsx8 b)\
					__attribute__((const));
t_3dcoordsx8	ft_3dunit8(t_3dcoordsx8 c)\
					__attribute__((const));
t_8packd		ft_3dclampsum8(t_3dcoordsx8 c)\
					__attribute__((const));
t_8packd		ft_3dnorm8(t_3dcoordsx8 c)\
					__attribute__((const));
t_8packd		ft_3ddot8(t_3dcoordsx8 a, t_3dcoordsx8 b)\
					__attribute__((const));

# ifdef __cplusplus
}
# endif

#endif
