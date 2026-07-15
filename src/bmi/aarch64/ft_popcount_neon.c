/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popcount_neon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if defined(__aarch64__) && FT_HAS_128_VEC

/*
 *	AArch64 has no scalar popcount instruction: cnt sums the population
 *	count of each of the 8 bytes of a NEON register independently, and
 *	addv folds those 8 per-byte counts into a single total in lane 0.
 *	The "w" constraints let the compiler place x/result in a vector
 *	register itself (and emit the fmov in/out), rather than pinning a
 *	fixed register here.
 */

__attribute__((__const__, __always_inline__))
inline t_u32a	ft_popcount_u32(t_u32a x)
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

__attribute__((__const__, __always_inline__))
inline t_u64a	ft_popcount_u64(t_u64a x)
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
