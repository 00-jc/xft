/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_ring_buffer_steal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 03:18:07 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 04:15:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/atomics.h>
#include <stdatomic.h>

__attribute__((__nonnull__(1), __always_inline__, __used__, __flatten__))
inline t_any	xft_ring_buffer_steal(t_ring_buffer *__restrict__ const rb)
{
	t_u32a			head;
	t_u32a			tail;
	const t_u32a	size = rb->size;
	t_any			slot;
	t_size			i;

	if (rb->memory == nullptr)
		__builtin_unreachable();
	i = 0;
	while (true)
	{
		head = atomic_load_explicit(&rb->head, xft_acquire);
		tail = atomic_load_explicit(&rb->tail, xft_acquire);
		slot = atomic_load_explicit(&rb->memory[head & (size - 1)],
				xft_acquire);
		if (__builtin_expect(tail == head, 0))
			return (nullptr);
		if (slot == nullptr)
			xft_backoff(++i);
		else if (__builtin_expect(atomic_compare_exchange_weak_explicit(
					&rb->head, &head, head + 1, xft_release, xft_relaxed), 1))
			break ;
	}
	atomic_store_explicit(&rb->memory[head & (size - 1)], nullptr, xft_release);
	return (slot);
}
