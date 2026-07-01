/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memctz.c                                        :+:      :+:    :+:   */
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
inline t_size	ft_memctz_u16(t_u16 x)
{
	t_u16	t;
	t_size	r;

	t = (t_u16)(((x & 0x00FF) == 0) << 3);
	x >>= t;
	r = (t_u8)t;
	t = (t_u16)(((x & 0x0F) == 0) << 2);
	x >>= t;
	r += t;
	t = (t_u16)(((x & 0x3) == 0) << 1);
	x >>= t;
	x &= 3;
	r += t;
	return (r + ((2 - (x >> 1)) & -((x & 1) == 0)));
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u32(t_u32 x)
{
	t_u32	t;
	t_size	r;

	t = (t_u32)((x & 0x0000FFFF) == 0) << 4;
	x >>= t;
	r = (t_u8)t;
	t = (t_u32)((x & 0x00FF) == 0) << 3;
	x >>= t;
	r += t;
	t = (t_u32)((x & 0x0F) == 0) << 2;
	x >>= t;
	r += t;
	t = (t_u32)((x & 0x3) == 0) << 1;
	x >>= t;
	x &= 3;
	r += t;
	return (r + ((2 - (x >> 1)) & -((x & 1) == 0)));
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u64(t_u64 x)
{
	t_u64	t;
	t_size	r;

	t = (t_u64)((x & 0x00000000FFFFFFFF) == 0) << 5;
	x >>= t;
	r = (t_u8)t;
	t = (t_u64)((x & 0x0000FFFF) == 0) << 4;
	x >>= t;
	r += t;
	t = (t_u64)((x & 0x00FF) == 0) << 3;
	x >>= t;
	r += t;
	t = (t_u64)((x & 0x0F) == 0) << 2;
	x >>= t;
	r += t;
	t = (t_u64)((x & 0x3) == 0) << 1;
	x >>= t;
	x &= 3;
	r += t;
	return (r + ((2 - (x >> 1)) & -((x & 1) == 0)));
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u128(t_u128 x)
{
	t_u128	t;
	t_size	r;

	t = (t_u128)((x & 0x0000000000000000FFFFFFFFFFFFFFFF) == 0) << 6;
	x >>= t;
	r = (t_u8)t;
	t = (t_u128)((x & 0x00000000FFFFFFFF) == 0) << 5;
	x >>= t;
	r += t;
	t = (t_u128)((x & 0x0000FFFF) == 0) << 4;
	x >>= t;
	r += t;
	t = (t_u128)((x & 0x00FF) == 0) << 3;
	x >>= t;
	r += t;
	t = (t_u128)((x & 0x0F) == 0) << 2;
	x >>= t;
	r += t;
	t = (t_u128)((x & 0x3) == 0) << 1;
	x >>= t;
	x &= 3;
	r += t;
	return (r + ((2 - (x >> 1)) & -((x & 1) == 0)));
}

#endif
