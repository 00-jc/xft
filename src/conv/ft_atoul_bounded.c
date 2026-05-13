/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul_bounded.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 17:47:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft.h"

__attribute__((__nonnull__(1)))
size_t	ft_atoul_bounded(const char *restrict const str, size_t n)
{
	size_t		out;
	size_t		i;

	out = 0;
	i = 0;
	while (ft_isspace(str[i]) && n--)
		++i;
	if (str[i] == '+')
		++i;
	while (str[i] && ft_isdigit(str[i]) && n--)
	{
		out = (out << 1) + (out << 3)
			+ ((size_t)str[i++] - '0');
	}
	return (out);
}
