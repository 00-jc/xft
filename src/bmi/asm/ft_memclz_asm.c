/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memclz_asm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 02:10:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/03 17:24:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if defined(__BMI__) && defined(__x86_64__)

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memclz_u16(t_u16 x)
{
	t_u16	result;

	__asm__("lzcnt %w1, %w0" : "=r"(result) : "r"(x));
	return (result);
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memclz_u32(t_u32 x)
{
	__asm__("lzcnt %1, %0" : "=r"(x) : "r"(x));
	return (x);
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memclz_u64(t_u64 x)
{
	__asm__("lzcnt %1, %0" : "=r"(x) : "r"(x));
	return (x);
}

__attribute__((hot, const, __always_inline__))
inline t_size	ft_memclz_u128(t_u128 x)
{
	t_u64	low;
	t_u64	high;

	low = (t_u64)x;
	high = (t_u64)(x >> 64);
	__asm__("lzcnt %1, %0" : "=r"(low) : "r"(low));
	__asm__("lzcnt %1, %0" : "=r"(high) : "r"(high));
	return ((high + (-(high >> 6) & low)));
}

#endif
