/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_extend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 04:37:39 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 05:16:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_str_reserve(t_str *restrict const str, size_t n)
{
	t_u8	*newalloc;
	t_u8	*old;
	size_t	new_cap;

	new_cap = n + str->capacity + 1;
	newalloc = ft_alloc(new_cap);
	if (__builtin_expect(newalloc != NULL, 1))
	{
		old = str->mem;
		ft_memcpy(newalloc, old, str->size + 1);
		ft_free((void **)&old);
		str->mem = newalloc;
		str->capacity = new_cap;
		return (1);
	}
	return (0);
}

__attribute__((__nonnull__(1, 2)))
int	ft_str_extend(t_str *restrict const str,
		const t_u8 *restrict const mem, size_t n)
{
	t_u8	should_extend;

	__attribute__((assume(str->mem != NULL)));
	{
		should_extend = str->capacity < str->size + n + 1;
		if (__builtin_expect(should_extend
				&& !ft_str_reserve(str, n), 0))
			return (0);
		ft_memcpy(str->mem + str->size, mem, n + 1);
		str->size += n;
	}
	return (1);
}
