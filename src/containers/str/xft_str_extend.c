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
		return ((t_result){.ok = KO, .err = xft_err_oom});
	str->buf.mem = new_buf.mem;
	str->buf.capacity = new_buf.size;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(2, 3)))
t_result	xft_str_extend(t_allocator allocator, t_str *restrict const str,
		const t_u8 *restrict const mem, t_size n)
{
	t_result	ret;

	if (str->buf.mem == nullptr)
		__builtin_unreachable();
	ret = (t_result){.ok = OK};
	if (__builtin_expect(str->buf.capacity < str->buf.size + n + 1, 0))
		ret = xft_str_reserve(allocator, str, n);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	xft_memcpy(str->buf.mem + str->buf.size, mem, n + 1);
	str->buf.size += n;
	return ((t_result){.ok = OK});
}
