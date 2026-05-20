/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 01:03:47 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/20 18:14:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "cstr.h"

__attribute__((__nonnull__(1)))
char	*ft_getenv(const char *restrict const var)
{
	size_t	idx;
	size_t	len;
	size_t	namelen;
	char	*value;

	if (__builtin_expect(!__environ, 0))
		return (nullptr);
	idx = 0;
	namelen = ft_strlen(var);
	while (__environ[idx])
	{
		len = ft_strlen(__environ[idx]);
		value = ft_memchr(__environ[idx], '=', len);
		if (!value)
		{
			idx++;
			continue ;
		}
		len = (size_t)((t_uptr)value - (t_uptr)__environ[idx]);
		if (len == namelen && !ft_memcmp(__environ[idx], var, namelen))
			return (value + 1);
		++idx;
	}
	return (nullptr);
}
