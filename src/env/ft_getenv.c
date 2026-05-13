/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 01:03:47 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:37:20 by jaicastr         ###   ########.fr       */
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

	if (__builtin_expect(!environ, 0))
		return (nullptr);
	idx = 0;
	namelen = ft_strlen(var);
	while (environ[idx])
	{
		len = ft_strlen(environ[idx]);
		value = ft_memchr(environ[idx], '=', len);
		if (!value)
		{
			idx++;
			continue ;
		}
		len = (size_t)((t_uptr)value - (t_uptr)environ[idx]);
		if (len == namelen && !ft_strncmp(environ[idx], var, namelen))
			return (value + 1);
		++idx;
	}
	return (nullptr);
}
