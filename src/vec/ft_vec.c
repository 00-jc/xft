/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 17:50:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec	ft_vec(t_allocator allocator, size_t size, size_t type_size)
{
	t_buffer	buf;
	size_t		mul;

	if (allocator.allocator == nullptr)
		__builtin_unreachable();
	mul = size * type_size;
	if (mul == 0 || (mul / size != type_size))
		return ((t_vec){0});
	buf = allocator.interface.allocate(allocator.allocator, mul,
			ft_next_pow2(mul));
	if (__builtin_expect(buf.mem == nullptr, 0))
		return ((t_vec){0});
	return ((t_vec){
		.size = 0,
		.capacity = buf.size / type_size,
		.buf = buf,
	});
}

__attribute__((__nonnull__(2)))
void	ft_vec_destroy(t_allocator allocator, t_vec *v)
{
	if (allocator.allocator == nullptr)
		__builtin_unreachable();
	if (v->buf.mem)
		allocator.interface.free(allocator.allocator, v->buf);
	*v = (t_vec){0};
}
