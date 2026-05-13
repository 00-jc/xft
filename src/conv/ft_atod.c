/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"

__attribute__((const, __always_inline__))
static inline t_f64	__eat_decimal(const char *s)
{
	t_f64	c;
	t_f64	out;

	c = 0.1;
	out = 0;
	while (*s && (*s >= '0' && *s <= '9'))
	{
		out += c * (*s++ - '0');
		c *= 0.1;
	}
	return (out);
}

__attribute__((pure, __nonnull__(1)))
t_f64	ft_atod(const char *s)
{
	int		neg;
	t_f64	out;

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
		out = (out * 10) + (*s++ - '0');
	if (*s == '.')
		s++;
	out += __eat_decimal(s);
	return (out * neg);
}
