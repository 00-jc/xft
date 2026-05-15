/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/01/19 04:38:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cstr.h"

__attribute__((__nonnull__(1)))
char	*ft_strdup(const char *str)
{
	size_t	n;
	char	*out;

	n = ft_strlen(str);
	out = malloc(n + 1);
	if (!out)
		return (nullptr);
	ft_memcpy(out, str, n + 1);
	return (out);
}
