/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_extend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:32:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 21:27:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(2), __always_inline__))
inline t_result	ft_vec_reserve(t_allocator allocator, t_vec *restrict const vec,
		size_t type_size, size_t n)
{
	t_buffer	new_buf;
	size_t		new_cap;

	new_cap = n + vec->capacity;
	new_buf = allocator.interface.realloc(allocator.allocator,
			vec->buf, new_cap * type_size, ft_next_pow2(new_cap * type_size));
	if (__builtin_expect(new_buf.mem != nullptr, 1))
	{
		vec->buf = new_buf;
		vec->capacity = new_buf.size / type_size;
		return (OK);
	}
	return (KO);
}

__attribute__((__nonnull__(2)))
t_result	ft_vec_extend(t_allocator allocator, t_vec *restrict const vec,
		t_buffer data, size_t type_size)
{
	size_t	n;
	t_u8	should_extend;

	n = data.size / type_size;
	if (vec->buf.mem == nullptr)
		__builtin_unreachable();
	{
		should_extend = vec->capacity < vec->size + n;
		if (__builtin_expect(should_extend
				&& !ft_vec_reserve(allocator, vec, type_size, n), 0))
			return (KO);
		ft_memcpy(vec->buf.mem + (vec->size * type_size),
			data.mem, data.size);
		vec->size += n;
	}
	return (OK);
}
