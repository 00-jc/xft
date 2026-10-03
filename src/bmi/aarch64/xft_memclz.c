/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memclz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#ifdef __aarch64__

__attribute__((hot, const, __always_inline__, __used__))
inline t_size	xft_memclz_u16(t_u16 x)
{
	t_u32	result;

	__asm__("clz %w0, %w1" : "=r"(result) : "r"((t_u32)x));
	return (result - 16);
}

__attribute__((hot, const, __always_inline__, __used__))
inline t_size	xft_memclz_u32(t_u32 x)
{
	__asm__("clz %w0, %w1" : "=r"(x) : "r"(x));
	return (x);
}

__attribute__((hot, const, __always_inline__, __used__))
inline t_size	xft_memclz_u64(t_u64 x)
{
	__asm__("clz %0, %1" : "=r"(x) : "r"(x));
	return (x);
}

__attribute__((hot, const, __always_inline__, __used__))
inline t_size	xft_memclz_u128(t_u128 x)
{
	t_u64	low;
	t_u64	high;

	low = (t_u64)x;
	high = (t_u64)(x >> 64);
	__asm__("clz %0, %1" : "=r"(low) : "r"(low));
	__asm__("clz %0, %1" : "=r"(high) : "r"(high));
	return ((high + (-(high >> 6) & low)));
}

#endif
