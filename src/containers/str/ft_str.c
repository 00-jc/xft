/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

t_str	ft_str(t_allocator allocator, t_size size)
{
	t_buffer	buf;

	if (__builtin_expect(size == 0, 0))
		return ((t_str){0});
	buf = allocator.interface.allocate(allocator.allocator, size + 1,
			ft_next_pow2(size + 1));
	if (__builtin_expect(buf.mem == nullptr, 0))
		return ((t_str){0});
	buf.mem[0] = 0;
	return ((t_str){.size = 0, .capacity = buf.size, .mem = buf.mem});
}

__attribute__((__nonnull__(2)))
void	ft_str_destroy(t_allocator allocator, t_str *str)
{
	if (allocator.allocator == nullptr)
		__builtin_unreachable();
	if (str->mem)
		allocator.interface.free(allocator.allocator,
			ft_fatptr(str->mem, str->capacity));
	*str = (t_str){0};
}
