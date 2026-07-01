/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memctz_asm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if defined(__BMI__) && defined(__x86_64__)

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u16(t_u16 x)
{
	t_u16	result;

	__asm__("tzcnt %w1, %w0" : "=r"(result) : "r"(x));
	return (result);
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u32(t_u32 x)
{
	__asm__("tzcnt %1, %0" : "=r"(x) : "r"(x));
	return (x);
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u64(t_u64 x)
{
	__asm__("tzcnt %1, %0" : "=r"(x) : "r"(x));
	return (x);
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memctz_u128(t_u128 x)
{
	t_u64	low;
	t_u64	high;

	low = (t_u64)x;
	high = (t_u64)(x >> 64);
	__asm__("tzcnt %1, %0" : "=r"(low) : "r"(low));
	__asm__("tzcnt %1, %0" : "=r"(high) : "r"(high));
	return ((low + (-(low >> 6) & high)));
}

#endif
