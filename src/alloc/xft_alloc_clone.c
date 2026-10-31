/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_alloc_clone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 02:03:26 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/alloc.h>
#include <xft/mem.h>

__attribute__((__flatten__))
t_buffer	xft_alloc_clone(t_allocator self, t_buffer buffer)
{
	t_buffer	mem;

	if (self.vtable == nullptr
		|| self.vtable->allocate == nullptr || buffer.mem == nullptr)
		__builtin_unreachable();
	mem = self.vtable->allocate(
			self.allocator, buffer.size,
			__GCC_CONSTRUCTIVE_SIZE);
	if (__builtin_expect(mem.mem == nullptr, 0))
		return (xft_fatptr(nullptr, 0));
	xft_memcpy(mem.mem, buffer.mem, buffer.size);
	return (mem);
}
