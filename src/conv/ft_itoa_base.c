/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft.h"

__attribute__((const, __always_inline__))
static inline ssize_t	_abs(ssize_t n)
{
	if (n < 0)
		return (-n);
	return (n);
}

__attribute__((const, __always_inline__))
static inline size_t	count(ssize_t n, ssize_t blen)
{
	size_t	c;

	c = 0;
	if (n < 0)
		c++;
	while (n != 0)
	{
		c++;
		n /= blen;
	}
	return (c);
}

static ssize_t	ft_ftalidate_base(char *base)
{
	char	*ptr;
	ssize_t	l;

	l = (ssize_t)ft_strlen(base);
	if (l < 2)
		return (-1);
	while (*base)
	{
		ptr = base + 1;
		while (*ptr)
			if (*base == *ptr++
				|| *base == '-'
				|| *base == '+')
				return (-1);
		base++;
	}
	return (l);
}

char	*ft_itoa_base(int n, char *base)
{
	ssize_t		blen;
	char		*out;
	size_t		c;

	blen = ft_ftalidate_base(base);
	if (blen == -1)
		return (nullptr);
	if (n == 0)
		return (ft_strdup("0"));
	out = ft_alloc(count(n, blen) + 1);
	if (!out)
		return (nullptr);
	c = count(n, blen);
	out[c] = 0;
	while (n != 0)
	{
		out[--c] = base[_abs(n % blen)];
		n /= (int)blen;
	}
	if (c == 1)
		out[--c] = '-';
	return (out);
}
