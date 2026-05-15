/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cstr.h"

__attribute__((__always_inline__, pure, __nonnull__(1)))
static inline unsigned int	count_words(char *str, char set)
{
	unsigned int	iw;
	unsigned int	wc;

	iw = 0;
	wc = 0;
	while (*str)
	{
		if (!iw && *str != set)
		{
			iw = 1;
			wc++;
		}
		if (iw && *str == set)
			iw = 0;
		str++;
	}
	return (wc);
}

__attribute__((__nonnull__(1)))
static char	*eat_literal(char *str, char set)
{
	int		i;
	char	*out;

	i = 0;
	while (str[i] && str[i] != set)
		i++;
	out = malloc((size_t)i + 1);
	if (!out)
		return (nullptr);
	i = 0;
	while (str[i] && str[i] != set)
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

__attribute__((__nonnull__(1, 3)))
static int	fill_words(const char *str, char set, char **out)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != set)
		{
			out[j] = eat_literal((char *)str + i, set);
			if (!out[j])
			{
				while (j--)
					free(out[j]);
				return (0);
			}
			j++;
			while (str[i] && str[i] != set)
				i++;
			continue ;
		}
		i++;
	}
	return (1);
}

__attribute__((pure, __nonnull__(1)))
char	**ft_split(const char *str, char set)
{
	char			**out;
	unsigned int	wc;

	wc = count_words((char *)str, set);
	out = malloc((wc + 1) * sizeof(char *));
	if (!out)
		return (nullptr);
	out[wc] = nullptr;
	if (!fill_words(str, set, out))
		return (free(out), nullptr);
	return (out);
}
