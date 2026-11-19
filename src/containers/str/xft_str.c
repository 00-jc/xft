/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/str.h>

__attribute__((__nonnull__(2)))
t_result	xft_new_str(t_allocator allocator, t_str *str, t_size size)
{
	t_buffer	buf;

	if (allocator.vtable == nullptr || allocator.vtable->allocate == nullptr)
		__builtin_unreachable();
	if (__builtin_expect(size == 0, 0))
		return ((t_result){.ok = KO, .err = xft_err_inval});
	buf = allocator.vtable->allocate(allocator.allocator, size + 1,
			__GCC_CONSTRUCTIVE_SIZE);
	if (__builtin_expect(buf.mem == nullptr, 0))
		return ((t_result){.ok = KO, .err = xft_err_oom});
	buf.mem[0] = 0;
	*str = (t_str){.buf = {.size = 0, .capacity = buf.size, .mem = buf.mem}};
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(2)))
void	xft_str_destroy(t_allocator allocator, t_str *str)
{
	if (allocator.allocator == nullptr || allocator.vtable == nullptr
		|| allocator.vtable->free == nullptr || str->buf.mem == nullptr)
		__builtin_unreachable();
	allocator.vtable->free(allocator.allocator,
		xft_fatptr(str->buf.mem, str->buf.capacity));
	*str = (t_str){0};
}
