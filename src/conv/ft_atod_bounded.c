/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod_bounded.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"
#include "ctype.h"

static inline t_f64	__eat_decimal(const char *s, size_t n)
{
	t_f64	c;
	t_f64	out;

	c = 0.1;
	out = 0;
	while (*s && ft_isdigit(*s) && n--)
	{
		out += c * (*s++ - '0');
		c *= 0.1;
	}
	return (out);
}

__attribute__((__nonnull__(1)))
t_f64	ft_atod_bounded(const char *s, size_t n)
{
	int		neg;
	t_f64	out;

	out = 0;
	neg = 1;
	if (*s == '-')
	{
		neg = -1;
		++s;
		--n;
	}
	else if (*s == '+')
	{
		++s;
		--n;
	}
	while (*s && *s != '.' && ft_isdigit(*s) && n--)
		out = (out * 10) + (*s++ - '0');
	if (*s == '.')
	{
		++s;
		--n;
	}
	out += __eat_decimal(s, n);
	return (out * neg);
}
