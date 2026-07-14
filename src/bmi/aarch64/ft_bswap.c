/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 22:08:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#ifdef __aarch64__

__attribute__((__always_inline__, const))
inline t_u16a	ft_bswap16(t_u16a x)
{
	t_u32a	new;

	__asm__ (
		"rev16 %w0, %w1"
		: "=r"(new)
		: "r"((t_u32a)x)
		);
	return ((t_u16a)new);
}

__attribute__((__always_inline__, const))
inline t_u32a	ft_bswap32(t_u32a x)
{
	t_u32a	new;

	__asm__ volatile (
		"rev %w0, %w1"
		: "=r"(new)
		: "r"(x)
	);
	return (new);
}

__attribute__((__always_inline__, const))
inline t_u64a	ft_bswap64(t_u64a x)
{
	t_u64a	new;

	__asm__ volatile (
		"rev %0, %1"
		: "=r"(new)
		: "r"(x)
	);
	return (new);
}

#endif
