/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_ring_buffer_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 01:05:54 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 03:39:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/atomics.h>
#include <xft/alloc.h>

__attribute__((__flatten__, __nonnull__(2)))
t_result	xft_new_ring_buffer(t_allocator allocator,
	t_ring_buffer *__restrict__ const rb, t_u32a min_size)
{
	t_buffer			buf;
	t_u32a				size;

	if (allocator.vtable == nullptr || allocator.vtable->allocate == nullptr)
		__builtin_unreachable();
	if (__builtin_expect((1ull << 31) < min_size || min_size == 0
			|| (t_u64)min_size * sizeof(t_atomicptr) > SIZE_MAX / 2 + 1, 0))
		return ((t_result){.ok = KO, .err = xft_err_inval});
	size = (t_u32a)xft_next_pow2((t_size)min_size);
	buf = allocator.vtable->allocate(allocator.allocator,
			size * sizeof(t_atomicptr), __GCC_CONSTRUCTIVE_SIZE);
	if (__builtin_expect(buf.mem == nullptr, 0))
		return ((t_result){.ok = KO, .err = xft_err_oom});
	xft_memset(buf.mem, 0, buf.size);
	rb->memory = (t_atomicptr *)buf.mem;
	rb->alloc_bytes = buf.size;
	rb->size = size;
	rb->head = 0;
	rb->tail = 0;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(2), __flatten__))
void	xft_destroy_ring_buffer(t_allocator allocator,
	t_ring_buffer *__restrict__ const rb)
{
	const t_buffer		b = xft_fatptr((t_any)rb->memory, rb->alloc_bytes);

	if (allocator.vtable == nullptr || allocator.vtable->free == nullptr
		|| rb->memory == nullptr)
		__builtin_unreachable();
	allocator.vtable->free(allocator.allocator, b);
}
