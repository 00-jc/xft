/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_ring_buffer_submit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 02:36:43 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 04:16:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/atomics.h>
#include <stdatomic.h>

__attribute__((__nonnull__(1), __always_inline__, __used__, __flatten__))
inline t_result	xft_ring_buffer_submit(t_ring_buffer *__restrict__ const rb,
	t_any ptr)
{
	t_u32a			head;
	t_u32a			tail;
	const t_u32a	size = rb->size;
	t_any			slot;
	t_size			i;

	if (rb->memory == nullptr || ptr == nullptr)
		__builtin_unreachable();
	i = 0;
	while (true)
	{
		tail = atomic_load_explicit(&rb->tail, xft_acquire);
		head = atomic_load_explicit(&rb->head, xft_acquire);
		slot = atomic_load_explicit(&rb->memory[tail & (size - 1)],
				xft_acquire);
		if (__builtin_expect(tail - head == size, 0))
			return (KO);
		else if (slot != nullptr)
			xft_backoff(++i);
		else if (__builtin_expect(atomic_compare_exchange_weak_explicit(
					&rb->tail, &tail, tail + 1, xft_release, xft_relaxed), 1))
			break ;
	}
	atomic_store_explicit(&rb->memory[tail & (size - 1)], ptr, xft_release);
	return (OK);
}
