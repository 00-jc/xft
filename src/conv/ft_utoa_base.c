/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 17:47:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft.h"

__attribute__((__always_inline__, pure))
static inline size_t	count(size_t n, size_t blen)
{
	size_t	c;

	c = 0;
	while (n != 0)
	{
		c++;
		n /= blen;
	}
	return (c);
}

__attribute__((__always_inline__, pure, __nonnull__(1)))
static inline ssize_t	ft_ftalidate_base(char *base)
{
	char	*ptr;
	ssize_t	l;

	l = ft_strlen(base);
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

__attribute__((__nonnull__(2)))
char	*ft_utoa_base(size_t n, char *base)
{
	size_t		blen;
	ssize_t		blen1;
	char		*out;
	size_t		c;

	blen1 = ft_ftalidate_base(base);
	if (blen1 == -1)
		return (nullptr);
	blen = (size_t) blen1;
	if (n == 0)
		return (ft_strdup("0"));
	out = malloc(count(n, blen) + 1);
	if (!out)
		return (nullptr);
	c = count(n, blen);
	out[c] = 0;
	while (n != 0)
	{
		out[--c] = base[n % blen];
		n /= blen;
	}
	if (c == 1)
		out[--c] = '-';
	return (out);
}
