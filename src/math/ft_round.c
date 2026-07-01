/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

__attribute__((__always_inline__, const))
inline t_f32	ft_floorf(t_f32 x)
{
	long long	i;
	long long	cnd;

	i = (long long)x;
	cnd = (t_f32)i > x;
	return ((t_f32)(((cnd & (i - 1))
			| (~cnd & i))));
}

__attribute__((__always_inline__, const))
inline t_f32	ft_ceilf(t_f32 x)
{
	long long	i;
	long long	cnd;

	i = (long long)x;
	cnd = (t_f32)i < x;
	return ((t_f32)(((cnd & (i + 1))
			| (~cnd & i))));
}

__attribute__((__always_inline__, const))
inline t_f32	ft_roundf(t_f32 x, t_u8 n)
{
	t_f32	p10;
	int		sign;
	t_f32	offset;

	if (n > 7)
		n = 7;
	p10 = 0.1f;
	while (n--)
		p10 *= 10.0f;
	sign = (x < 0);
	offset = 0.5f - (t_f32)sign;
	return ((ft_floorf(x * p10 + offset) * (t_f32)(1 - sign)
		+ ft_ceilf(x * p10 + offset) * (t_f32)sign) / p10);
}

__attribute__((__always_inline__, const))
inline t_f32	ft_roundff(t_f32 x)
{
	return ((t_f32)((x >= 0.0f) * (int)(x + 0.5f)
				| (x < 0.0f) * (int)(x - 0.5f)));
}
