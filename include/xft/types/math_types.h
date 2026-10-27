/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_TYPES_H
# define MATH_TYPES_H

# include <xft/mem.h>

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

typedef t_4packd	t_3dcoords;

#endif
