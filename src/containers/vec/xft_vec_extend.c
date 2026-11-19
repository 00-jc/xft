/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_vec_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 13:31:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/vec.h>

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_result	xft_vec_reserve(t_allocator allocator,
	t_vec *restrict const vec, t_size n)
{
	t_buffer	new_buf;
	t_size		new_cap;

	if (allocator.vtable == nullptr || allocator.vtable->realloc == nullptr)
		__builtin_unreachable();
	new_cap = n + vec->buf.capacity;
	new_buf = allocator.vtable->realloc(allocator.allocator,
			xft_fatptr(vec->buf.mem, vec->buf.capacity), new_cap,
			__GCC_CONSTRUCTIVE_SIZE);
	if (__builtin_expect(new_buf.mem != nullptr, 1))
	{
		vec->buf.mem = new_buf.mem;
		vec->buf.capacity = new_buf.size;
		return ((t_result){.ok = OK});
	}
	return ((t_result){.ok = KO, .err = xft_err_oom});
}

__attribute__((__nonnull__(2)))
t_result	xft_vec_extend(t_allocator allocator,
		t_vec *restrict const vec, t_buffer data)
{
	t_result	ret;

	if (vec->buf.mem == nullptr)
		__builtin_unreachable();
	{
		ret = (t_result){.ok = OK};
		if (__builtin_expect(vec->buf.capacity < vec->buf.size + data.size, 0))
			ret = xft_vec_reserve(allocator, vec, data.size);
		if (__builtin_expect(!ret.ok, 0))
			return (ret);
		xft_memcpy(vec->buf.mem + vec->buf.size, data.mem, data.size);
		vec->buf.size += data.size;
	}
	return ((t_result){.ok = OK});
}
