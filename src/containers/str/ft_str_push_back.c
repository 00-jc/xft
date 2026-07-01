/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

__attribute__((__nonnull__(2)))
t_result	ft_str_push_back(t_allocator allocator,
		t_str *restrict const str, const t_u8 byte)
{
	if (str->mem == nullptr || allocator.allocator == nullptr)
		__builtin_unreachable();
	if (__builtin_expect(str->size + 1 >= str->capacity
			&& !ft_str_reserve(allocator, str,
				ft_tern(str->capacity, str->capacity << 1, 4)), 0))
		return (KO);
	str->mem[str->size++] = byte;
	str->mem[str->size] = 0;
	return (OK);
}
