/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_extend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 04:37:39 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 16:56:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

__attribute__((__nonnull__(2)))
int	ft_str_reserve(t_allocator allocator,
	t_str *restrict const str, size_t n)
{
	t_buffer	new_buf;
	size_t		new_cap;

	if (str->mem == nullptr || allocator.allocator == nullptr)
		__builtin_unreachable();
	new_cap = n + str->capacity + 1;
	new_buf = allocator.interface.realloc(allocator.allocator,
			ft_fatptr(str->mem, str->capacity), new_cap, ft_next_pow2(new_cap));
	if (__builtin_expect(new_buf.mem == nullptr, 0))
		return (0);
	str->mem = new_buf.mem;
	str->capacity = new_buf.size;
	return (1);
}

__attribute__((__nonnull__(2, 3)))
int	ft_str_extend(t_allocator allocator, t_str *restrict const str,
		const t_u8 *restrict const mem, size_t n)
{
	t_u8	should_extend;

	if (str->mem == nullptr)
		__builtin_unreachable();
	should_extend = str->capacity < str->size + n + 1;
	if (__builtin_expect(should_extend
			&& !ft_str_reserve(allocator, str, n), 0))
		return (0);
	ft_memcpy(str->mem + str->size, mem, n + 1);
	str->size += n;
	return (1);
}
