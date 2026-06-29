/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:02:57 by username          #+#    #+#             */
/*   Updated: 2026/06/28 16:02:59 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_TYPES_H
# define MATH_TYPES_H

# include "primitives.h"

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

#endif
