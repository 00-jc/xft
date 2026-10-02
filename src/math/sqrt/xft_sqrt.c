/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 15:13:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

#ifdef __x86_64__

__attribute__((__always_inline__, const, __used__))
inline t_f32	xft_sqrt(t_f32 number)
{
	__asm__("sqrtss %1, %0" : "=x"(number) : "x"(number));
	return (number);
}

__attribute__((__always_inline__, const, __used__))
inline t_f64	xft_dsqrt(t_f64 number)
{
	__asm__("sqrtsd %1, %0" : "=x"(number) : "x"(number));
	return (number);
}

#else

__attribute__((__always_inline__, const, __used__))
inline t_f32	xft_sqrt(t_f32 number)
{
	t_u32a		i;
	t_f32		x2;
	t_f32		y;
	t_fp		fp;
	t_f32		threehalfs;

	if (number < 0)
		return (-1);
	threehalfs = 1.5F;
	x2 = number * 0.5F;
	y = number;
	fp.f = y;
	i = fp.i;
	i = 0x5F3759DF - (i >> 1);
	fp.i = i;
	y = fp.f;
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));
	return (number * y);
}

__attribute__((__always_inline__, const, __used__))
inline t_f64	xft_dsqrt(t_f64 number)
{
	t_u64a	i;
	t_f64	x2;
	t_f64	y;
	t_dp	fp;
	t_f64	threehalfs;

	if (number < 0)
		return (-1);
	threehalfs = 1.5;
	x2 = number * 0.5;
	y = number;
	fp.f = y;
	i = fp.i;
	i = 0x5FE6EC85E7DE30DA - (i >> 1);
	fp.i = i;
	y = fp.f;
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));
	return (number * y);
}

#endif
