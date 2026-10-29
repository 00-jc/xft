/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 00:16:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/vec.h>

t_vec	xft_new_vec(t_allocator allocator, t_size size, t_size type_size)
{
	t_buffer	buf;
	t_size		res;

	if (allocator.allocator == nullptr
		|| allocator.vtable.allocate == nullptr)
		__builtin_unreachable();
	if ((size == 0) || (type_size == 0)
		|| __builtin_mul_overflow(size, type_size, &res))
		return ((t_vec){0});
	buf = allocator.vtable.allocate(allocator.allocator, res,
			__GCC_CONSTRUCTIVE_SIZE);
	if (__builtin_expect(buf.mem == nullptr, 0))
		return ((t_vec){0});
	return ((t_vec){
		.size = 0,
		.buf = buf,
	});
}

__attribute__((__always_inline__, __nonnull__(2), __used__))
inline void	xft_vec_destroy(t_allocator allocator, t_vec *v)
{
	if (allocator.allocator == nullptr
		|| allocator.vtable.free == nullptr || v->buf.mem == nullptr)
		__builtin_unreachable();
	if (v->buf.mem)
		allocator.vtable.free(allocator.allocator, v->buf);
	*v = (t_vec){0};
}
