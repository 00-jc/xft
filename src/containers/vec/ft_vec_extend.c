/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_extend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 13:31:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(2), __always_inline__))
inline t_result	ft_vec_reserve(t_allocator allocator, t_vec *restrict const vec,
	size_t n)
{
	t_buffer	new_buf;
	size_t		new_cap;

	new_cap = n + vec->buf.size;
	new_buf = allocator.interface.realloc(allocator.allocator,
			vec->buf, new_cap, ft_next_pow2(new_cap));
	if (__builtin_expect(new_buf.mem != nullptr, 1))
	{
		vec->buf = new_buf;
		return (OK);
	}
	return (KO);
}

__attribute__((__nonnull__(2)))
t_result	ft_vec_extend(t_allocator allocator,
		t_vec *restrict const vec, t_buffer data)
{
	t_u8	should_extend;

	if (vec->buf.mem == nullptr)
		__builtin_unreachable();
	{
		should_extend = vec->buf.size < vec->size + data.size;
		if (__builtin_expect(should_extend
				&& !ft_vec_reserve(allocator, vec, data.size), 0))
			return (KO);
		ft_memcpy(vec->buf.mem + vec->size, data.mem, data.size);
		vec->size += data.size;
	}
	return (OK);
}
