/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_clone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "bmi.h"
#include "mem.h"

__attribute__((__nonnull__(1)))
t_buffer	ft_alloc_clone(void *self, t_buffer buffer)
{
	t_buffer	mem;

	mem = ((t_allocator *)self)->interface.allocate(
			((t_allocator *)self)->allocator, buffer.size,
			ft_next_pow2(buffer.size));
	if (__builtin_expect(mem.mem == nullptr, 0))
		return (ft_fatptr(nullptr, 0));
	ft_memcpy(mem.mem, buffer.mem, buffer.size);
	return (mem);
}
