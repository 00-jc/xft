/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memclz_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>

#if __has_builtin(__builtin_clzg)

__attribute__((hot, const, __always_inline__, __used__))
inline t_size	xft_memclz_u16(t_u16 x)
{
	return ((t_size)__builtin_clzg(x, 16));
}

__attribute__((hot, const, __always_inline__, __used__))
inline t_size	xft_memclz_u32(t_u32 x)
{
	return ((t_size)__builtin_clzg(x, 32));
}

__attribute__((hot, const, __always_inline__, __used__))
inline t_size	xft_memclz_u64(t_u64 x)
{
	return ((t_size)__builtin_clzg(x, 64));
}

__attribute__((hot, const, __always_inline__, __used__))
inline t_size	xft_memclz_u128(t_u128 x)
{
	return ((t_size)__builtin_clzg(x, 128));
}

#endif
