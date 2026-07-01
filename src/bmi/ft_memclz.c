/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memclz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if !defined(__BMI__) || !defined(__x86_64__)

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memclz_u16(t_u16 x)
{
	t_u16	t;
	t_size	r;

	t = (t_u16)(((x & 0xFF00) == 0) << 3);
	x >>= 8 - t;
	r = t;
	t = (t_u16)(((x & 0xF0) == 0) << 2);
	x >>= 4 - t;
	r += t;
	t = (t_u16)(((x & 0xC) == 0) << 1);
	x >>= 2 - t;
	r += t;
	return (r + ((2 - x) & -((x & 2) == 0)));
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memclz_u32(t_u32 x)
{
	t_u32	t;
	t_size	r;

	t = (t_u32)((x & 0xFFFF0000) == 0) << 4;
	x >>= 16 - t;
	r = t;
	t = (t_u32)((x & 0xFF00) == 0) << 3;
	x >>= 8 - t;
	r += t;
	t = (t_u32)((x & 0xF0) == 0) << 2;
	x >>= 4 - t;
	r += t;
	t = (t_u32)((x & 0xC) == 0) << 1;
	x >>= 2 - t;
	r += t;
	return (r + ((2 - x) & -((x & 2) == 0)));
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memclz_u64(t_u64 x)
{
	t_u64	t;
	t_size	r;

	t = (t_u64)((x & 0xFFFFFFFF00000000) == 0) << 5;
	x >>= 32 - t;
	r = t;
	t = (t_u64)((x & 0xFFFF0000) == 0) << 4;
	x >>= 16 - t;
	r += t;
	t = (t_u64)((x & 0xFF00) == 0) << 3;
	x >>= 8 - t;
	r += t;
	t = (t_u64)((x & 0xF0) == 0) << 2;
	x >>= 4 - t;
	r += t;
	t = (t_u64)((x & 0xC) == 0) << 1;
	x >>= 2 - t;
	r += t;
	return (r + ((2 - x) & -((x & 2) == 0)));
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memclz_u128(t_u128 x)
{
	t_u128	t;
	t_size	r;

	t = (t_u128)((x & ~0x0000000000000000FFFFFFFFFFFFFFFF) == 0) << 6;
	x >>= 64 - t;
	r = (t_size)t;
	t = (t_u128)((x & 0xFFFFFFFF00000000) == 0) << 5;
	x >>= 32 - t;
	r += t;
	t = (t_u128)((x & 0xFFFF0000) == 0) << 4;
	x >>= 16 - t;
	r += t;
	t = (t_u128)((x & 0xFF00) == 0) << 3;
	x >>= 8 - t;
	r += t;
	t = (t_u128)((x & 0xF0) == 0) << 2;
	x >>= 4 - t;
	r += t;
	t = (t_u128)((x & 0xC) == 0) << 1;
	x >>= 2 - t;
	r += t;
	return (r + ((2 - x) & -((x & 2) == 0)));
}

#endif
