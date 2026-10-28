/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_xxh3_mul128_fold64.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_xxh3.h>

#ifdef __SIZEOF_INT128__

__attribute__((__always_inline__, const, __used__))
inline t_u64a	xft_xxh3_mul128_fold64(t_u64a a, t_u64a b)
{
	t_u128a	x;

	x = (t_u128a)a * (t_u128a)b;
	return ((t_u64a)(x) ^ (t_u64a)(x >> 64));
}

#else

// upstream's XXH_mult64to128 scalar path, 32x32->64 partial products
__attribute__((__always_inline__, const, __used__))
inline t_u64a	xft_xxh3_mul128_fold64(t_u64a a, t_u64a b)
{
	t_u64a	lo_lo;
	t_u64a	hi_lo;
	t_u64a	lo_hi;
	t_u64a	cross;
	t_u64a	upper;

	lo_lo = (t_u64a)(t_u32a)a * (t_u32a)b;
	hi_lo = (a >> 32) * (t_u32a)b;
	lo_hi = (t_u64a)(t_u32a)a * (b >> 32);
	cross = (lo_lo >> 32) + (t_u32a)hi_lo + lo_hi;
	upper = (hi_lo >> 32) + (cross >> 32) + (a >> 32) * (b >> 32);
	return ((cross << 32 | (t_u32a)lo_lo) ^ upper);
}

#endif
