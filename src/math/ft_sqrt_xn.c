/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_xn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_math.h"

#if FT_HAS_512_VEC

__attribute__((__always_inline__, const))
inline t_8packd	ft_dsqrt_x8(t_8packd pck)
{
	t_v8da	v;

	v = *(const t_v8da * restrict const) & pck;
	__asm__("vsqrtpd %1, %0" : "=x"(v) : "x"(v));
	return (*(const t_8packd * restrict const) & v);
}

#elif FT_HAS_256_VEC

__attribute__((__always_inline__, const))
inline t_8packd	ft_dsqrt_x8(t_8packd pck)
{
	t_v4da	v1;
	t_v4da	v2;

	v1 = *(const t_v4da * restrict const) & pck;
	v2 = *(const t_v4da * restrict const) & pck.a;
	__asm__("vsqrtpd %1, %0" : "=x"(v1) : "x"(v1));
	__asm__("vsqrtpd %1, %0" : "=x"(v2) : "x"(v2));
	return ((t_8packd){v1[0], v1[1], v1[2], v1[3],
		v2[0], v2[1], v2[2], v2[3]});
}

#else

__attribute__ ((__always_inline__, const))
inline t_8packd	ft_dsqrt_x8(t_8packd d1)
{
	t_v8u64a	i;
	t_v8da		x2;
	t_v8da		y;
	t_v8da		threehalfs;

	threehalfs = (t_v8da){1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5};
	y = *(const t_v8da * restrict const) & d1;
	x2 = y * 0.5;
	i = (t_v8di){.d = y}.i;
	i = 0x5FE6EC85E7DE30DA - (i >> 1);
	y = (t_v8di){.i = i}.d;
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));
	y *= *(const t_v8da * restrict const) & d1;
	return (*(const t_8packd * restrict const) & y);
}

#endif
