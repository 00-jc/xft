/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drsqrt_xn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_math.h"

__attribute__ ((__always_inline__, const))
inline t_4packd	ft_drsqrt_x4(t_4packd d1)
{
	t_v4u64a	i;
	t_v4da		x2;
	t_v4da		y;
	t_v4da		threehalfs;

	threehalfs = (t_v4da){1.5, 1.5, 1.5, 1.5};
	y = *(const t_v4da * restrict const) & d1;
	x2 = y * 0.5;
	i = (t_v4di){.d = y}.i;
	i = 0x5FE6EC85E7DE30DA - (i >> 1);
	y = (t_v4di){.i = i}.d;
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));
	return (*(const t_4packd * restrict const) & y);
}

__attribute__ ((__always_inline__, const))
inline t_8packd	ft_drsqrt_x8(t_8packd d1)
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
	return (*(const t_8packd * restrict const) & y);
}
