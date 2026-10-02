/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_pow_signed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

__attribute__((__always_inline__, const, __used__))
inline int	xft_ipow(int x, t_u64 n)
{
	int	res;

	res = 1;
	while (n)
	{
		if ((n & 1) == 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

__attribute__((__always_inline__, const, __used__))
inline long long	xft_lpow(long long x, t_u64 n)
{
	long long	res;

	res = 1;
	while (n)
	{
		if ((n & 1) == 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

__attribute__((__always_inline__, const, __used__))
inline t_f32	xft_fpow(t_f32 x, t_u64 n)
{
	t_f32	res;

	res = 1;
	while (n)
	{
		if ((n & 1) == 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

__attribute__((__always_inline__, const, __used__))
inline t_f64	xft_dpow(t_f64 x, t_u64 n)
{
	t_f64	res;

	res = 1.0;
	while (n)
	{
		if ((n & 1) == 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}
