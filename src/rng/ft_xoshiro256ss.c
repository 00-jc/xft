/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xoshiro256ss.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 19:00:27 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/15 13:09:59 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rng.h"

__attribute__((__nonnull__(1), __always_inline__))
inline t_u64a	ft_splitmix(t_u64a *restrict const x)
{
	t_u64a	z;

	*x += 0x9E3779B97F4A7C15;
	z = *x;
	z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9;
	z = (z ^ (z >> 27)) * 0x94D049BB133111EB;
	return (z ^ (z >> 31));
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_xoshiro_init(t_xoshiro xoshiro)
{
	static t_size	internal = 0x165667919E3779F9ULL;
	t_size			current;
	t_u64a			x;

	internal += ((t_uptr)xoshiro) << 3;
	x = (t_uptr) & current ^ internal++;
	xoshiro[0] = ft_splitmix(&x) | 1;
	xoshiro[1] = ft_splitmix(&x) | 2;
	xoshiro[2] = ft_splitmix(&x) | 4;
	xoshiro[3] = ft_splitmix(&x) | 8;
}

__attribute__((__nonnull__(1), __always_inline__))
inline t_u64a	ft_xoshiro256ss(t_xoshiro xoshi)
{
	t_u64a	t3;
	t_u64a	res;
	t_u64a	t;

	t3 = xoshi[1];
	t3 = t3 + (t3 << 1);
	res = ft_rotl64(t3, 7);
	res = res + (res << 3);
	t = xoshi[1] << 17;
	xoshi[2] ^= xoshi[0];
	xoshi[3] ^= xoshi[1];
	xoshi[1] ^= xoshi[2];
	xoshi[0] ^= xoshi[3];
	xoshi[2] ^= t;
	xoshi[3] = ft_rotl64(xoshi[3], 45);
	return (res);
}
