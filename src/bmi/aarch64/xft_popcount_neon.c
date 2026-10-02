/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_popcount_neon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if defined(__aarch64__) && XFT_HAS_128_VEC

__attribute__((__const__, __always_inline__, __used__))
inline t_u32a	xft_popcount_u32(t_u32a x)
{
	t_u32a	result;

	__asm__ (
		"cnt  %0.8b, %1.8b\n\t"
		"addv %b0, %0.8b"
		: "=w"(result)
		: "w"(x)
		);
	return (result);
}

__attribute__((__const__, __always_inline__, __used__))
inline t_u64a	xft_popcount_u64(t_u64a x)
{
	t_u64a	result;

	__asm__ (
		"cnt  %0.8b, %1.8b\n\t"
		"addv %b0, %0.8b"
		: "=w"(result)
		: "w"(x)
		);
	return (result);
}

#endif
