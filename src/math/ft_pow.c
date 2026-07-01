/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

__attribute__((__always_inline__, const))
inline t_u8	ft_pow_u8(t_u8 x, t_u8 n)
{
	t_u8	res;

	res = 1;
	while (n)
	{
		if (n & 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

__attribute__((__always_inline__, const))
inline t_u32	ft_pow_u32(t_u32 x, t_u32 n)
{
	t_u32	res;

	res = 1;
	while (n)
	{
		if (n & 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

__attribute__((__always_inline__, const))
inline t_u64	ft_pow_u64(t_u64 x, t_u64 n)
{
	t_u64	res;

	res = 1;
	while (n)
	{
		if (n & 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}

__attribute__((__always_inline__, const))
inline t_u128	ft_pow_u128(t_u128 x, t_u128 n)
{
	t_u128	res;

	res = 1;
	while (n)
	{
		if (n & 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return (res);
}
