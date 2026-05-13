/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cstr.h"

__attribute__((__nonnull__(1, 2)))
char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t			l1;
	size_t			l2;
	char			*out;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	out = ft_alloc(l1 + l2 + 1);
	if (!out)
		return (nullptr);
	ft_memcpy(out, s1, l1);
	ft_memcpy(out + l1, s2, l2);
	out[l1 + l2] = 0;
	return (out);
}
