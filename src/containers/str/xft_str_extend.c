/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_str_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/str.h>

__attribute__((__nonnull__(2)))
t_result	xft_str_reserve(t_allocator allocator,
	t_str *restrict const str, t_size n)
{
	t_buffer	new_buf;
	t_size		new_cap;

	if (str->buf.mem == nullptr || allocator.allocator == nullptr
		|| allocator.vtable == nullptr || allocator.vtable->realloc == nullptr)
		__builtin_unreachable();
	new_cap = n + str->buf.capacity + 1;
	new_buf = allocator.vtable->realloc(allocator.allocator,
			xft_fatptr(str->buf.mem, str->buf.capacity), new_cap,
			__GCC_CONSTRUCTIVE_SIZE);
	if (__builtin_expect(new_buf.mem == nullptr, 0))
		return (KO);
	str->buf.mem = new_buf.mem;
	str->buf.capacity = new_buf.size;
	return (OK);
}

__attribute__((__nonnull__(2, 3)))
t_result	xft_str_extend(t_allocator allocator, t_str *restrict const str,
		const t_u8 *restrict const mem, t_size n)
{
	t_u8	should_extend;

	if (str->buf.mem == nullptr)
		__builtin_unreachable();
	should_extend = str->buf.capacity < str->buf.size + n + 1;
	if (__builtin_expect(should_extend
			&& !xft_str_reserve(allocator, str, n), 0))
		return (KO);
	xft_memcpy(str->buf.mem + str->buf.size, mem, n + 1);
	str->buf.size += n;
	return (OK);
}
