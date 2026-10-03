/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_popcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:48:32 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 13:45:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

#if !defined(__x86_64__) && !(defined(__aarch64__) && XFT_HAS_128_VEC)

__attribute__((__const__, __always_inline__, __used__))
inline t_u64a	xft_popcount_u64(t_u64a x)
{
	t_u64a	x2;
	t_u32a	x1;

	x2 = x;
	x2 = x2 - ((x2 >> 1) & 0x5555555555555555ULL);
	x2 = ((x2 >> 2) & 0x3333333333333333ULL) + (x2 & 0x3333333333333333ULL);
	x2 = (x2 + (x2 >> 4)) & 0x0F0F0F0F0F0F0F0FuLL;
	x1 = (t_u32a)(x2 + (x2 >> 32));
	x = x + (x >> 16);
	return ((x + (x >> 8)) & 0x0000007F);
}

__attribute__((__const__, __always_inline__, __used__))
inline t_u32a	xft_popcount_u32(t_u32a x)
{
	x = x - ((x >> 1) & 0x55555555);
	x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
	x = (x + (x >> 4)) & 0x0F0F0F0F;
	x = (x + (x >> 16));
	return ((x + (x >> 8)) & 0x0000003F);
}

#endif
