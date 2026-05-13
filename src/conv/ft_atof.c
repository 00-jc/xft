/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:48:39 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"

__attribute__((const, __always_inline__, __nonnull__(1)))
static inline t_f32	__eat_decimal(const char *s)
{
	t_f32	c;
	t_f32	out;

	c = 0.1f;
	out = 0;
	while (*s && (*s >= '0' && *s <= '9'))
	{
		out += c * (t_f32)(*s++ - '0');
		c *= 0.1f;
	}
	return (out);
}

__attribute__((pure, __nonnull__(1)))
t_f32	ft_atof(const char *s)
{
	int		neg;
	t_f32	out;

	out = 0;
	neg = 1;
	if (*s == '-')
	{
		neg = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s && *s != '.' && (*s >= '0' && *s <= '9'))
		out = (out * 10) + (t_f32)(*s++ - '0');
	if (*s == '.')
		s++;
	out += __eat_decimal(s);
	return (out * (t_f32)neg);
}
