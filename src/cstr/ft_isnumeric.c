/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 17:47:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft.h"

__attribute__((__nonnull__(1)))
inline t_u8	ft_isunum(const char *restrict s,
	size_t size)
{
	char	c;

	if (!size)
		return (0);
	if (*s == '+')
	{
		++s;
		--size;
	}
	while (size-- > 0)
	{
		c = *s++;
		if (!ft_isdigit(c))
			return (0);
	}
	return (1);
}
