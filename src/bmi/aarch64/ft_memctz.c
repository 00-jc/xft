/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memctz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 22:09:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#ifdef __aarch64__

/*
 *	AArch64 has no native trailing-zero-count instruction: tzcnt(x) is
 *	built as clz(rbit(x)), the standard idiom (rbit mirrors the bit
 *	order so the low set bit becomes the high set bit for clz to find).
 *	At native register width clz-of-zero already yields the width, so
 *	x == 0 falls out correctly with no extra handling. For the 16-bit
 *	case the register is wider than the value, so a guard bit is set
 *	just above the value's width: it only gets "seen" by clz when the
 *	real 16 bits are all zero, at which point it forces the result to
 *	exactly 16, mirroring x86_64's tzcnt semantics on a 16-bit operand.
 */

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u16(t_u16 x)
{
	t_u32	y;
	t_u32	result;

	y = (t_u32)x | 0x10000U;
	__asm__(
		"rbit %w0, %w1\n\t"
		"clz  %w0, %w0"
		: "=r"(result)
		: "r"(y)
		);
	return (result);
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u32(t_u32 x)
{
	__asm__(
		"rbit %w0, %w1\n\t"
		"clz  %w0, %w0"
		: "=r"(x)
		: "r"(x)
		);
	return (x);
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u64(t_u64 x)
{
	__asm__(
		"rbit %0, %1\n\t"
		"clz  %0, %0"
		: "=r"(x)
		: "r"(x)
		);
	return (x);
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u128(t_u128 x)
{
	t_u64	low;
	t_u64	high;

	low = (t_u64)x;
	high = (t_u64)(x >> 64);
	__asm__(
		"rbit %0, %1\n\t"
		"clz  %0, %0"
		: "=r"(low)
		: "r"(low)
		);
	__asm__(
		"rbit %0, %1\n\t"
		"clz  %0, %0"
		: "=r"(high)
		: "r"(high)
		);
	return ((low + (-(low >> 6) & high)));
}

#endif
