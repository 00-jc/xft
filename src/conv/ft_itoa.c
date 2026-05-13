/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 17:47:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft.h"

__attribute__((const, __always_inline__))
static inline unsigned int	count(int n)
{
	unsigned int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

__attribute__((const, __always_inline__))
static inline int	_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

char	*ft_itoa(int n)
{
	int				neg;
	char			*out;
	unsigned int	cc;

	cc = count(n);
	neg = 1;
	out = ft_alloc(cc + 1);
	if (!out)
		return (nullptr);
	if (n < 0)
	{
		out[0] = '-';
		neg = -1;
	}
	out[cc] = 0;
	while (cc > 0 || n != 0)
	{
		if (neg == -1 && cc == 1)
			break ;
		out[--cc] = '0' + (char)(_abs(n % 10));
		n /= 10;
	}
	return (out);
}
