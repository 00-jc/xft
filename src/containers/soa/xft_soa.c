/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_soa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 23:47:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 00:19:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/soa.h>

__attribute__((__nonnull__(3)))
t_soa	xft_new_soa(t_allocator allocator, t_size element_size_capacity,
	const t_soa_context *__restrict__ const context)
{
	t_buffer		buf;

	if (allocator.allocator == nullptr || allocator.vtable == nullptr
		|| allocator.vtable->allocate == nullptr)
		__builtin_unreachable();
	if (__builtin_expect(element_size_capacity == 0
			|| context->total_struct_size == 0
			|| context->max_alignment == 0
			|| (context->max_alignment
				& (context->max_alignment - 1)) != 0, 0))
		return ((t_soa){0});
	element_size_capacity = (element_size_capacity
			+ context->max_alignment - 1)
		& ~(context->max_alignment - 1);
	buf = allocator.vtable->allocate(allocator.allocator,
			element_size_capacity * context->total_struct_size,
			xft_max_s(context->max_alignment, __GCC_CONSTRUCTIVE_SIZE));
	if (__builtin_expect(buf.mem == nullptr, 0))
		return ((t_soa){0});
	return ((t_soa){.ptr = buf.mem,
		.allocator_bytes_given = buf.size,
		.capacity_elements = element_size_capacity,
		.occupied_elements = 0});
}

__attribute__((__nonnull__(2)))
void	xft_destroy_soa(t_allocator allocator, t_soa *soa)
{
	if (allocator.allocator == nullptr || allocator.vtable == nullptr
		|| allocator.vtable->free == nullptr)
		__builtin_unreachable();
	if (soa->ptr)
		allocator.vtable->free(allocator.allocator,
			xft_fatptr(soa->ptr, soa->allocator_bytes_given));
	*soa = (t_soa){0};
}
