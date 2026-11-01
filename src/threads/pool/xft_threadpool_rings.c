/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_rings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 02:54:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 13:50:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_threadpool.h>

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline void	xft__free_rings(t_allocator allocator, t_threadpool *tp, t_size it)
{
	t_size		it2;

	if (allocator.vtable == nullptr || allocator.vtable->free == nullptr)
		__builtin_unreachable();
	it2 = 0;
	while (it2 < it)
		xft_destroy_ring_buffer(allocator, &tp->worker_rings[it2++]);
	allocator.vtable->free(allocator.allocator,
		xft_fatptr((t_any)tp->worker_rings, tp->rings_alloc_size));
	tp->worker_rings = nullptr;
}

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_result	xft__init_rings(t_allocator allocator, t_threadpool *tp)
{
	t_size			it;
	const t_size	upper_bound = tp->n_workers;
	t_ring_buffer	rb;
	t_buffer		buffer;

	if (allocator.allocator == nullptr || allocator.vtable == nullptr
		|| allocator.vtable->allocate == nullptr)
		__builtin_unreachable();
	buffer = allocator.vtable->allocate(allocator.allocator,
			upper_bound * sizeof(t_ring_buffer), _Alignof(t_ring_buffer));
	if (__builtin_expect(buffer.mem == nullptr, 0))
		return (KO);
	tp->rings_alloc_size = buffer.size;
	tp->worker_rings = (t_any)buffer.mem;
	it = 0;
	while (it < upper_bound)
	{
		rb = xft_new_ring_buffer(allocator, 256);
		if (__builtin_expect(rb.memory == nullptr, 0))
			return ((void)(xft__free_rings(allocator, tp, it)), KO);
		tp->worker_rings[it++] = rb;
	}
	return (OK);
}
