/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:32:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

__attribute__((__nonnull__(1), __always_inline__, hot))
inline int	ft_str_push_back(t_str *restrict const str,
		const t_u8 byte)
{
	__attribute__((assume(str->mem != nullptr)));
	{
		if (__builtin_expect(str->size + 1 >= str->capacity
				&& !ft_str_reserve(str,
					ft_tern(str->capacity, str->capacity << 1, 4)), 0))
			return (0);
		str->mem[str->size++] = byte;
		str->mem[str->size] = 0;
		return (1);
	}
}
