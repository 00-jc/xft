/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_read_completion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/linux/uring.h>
#include <stdatomic.h>

__attribute__((__nonnull__(1, 2)))
t_result	xft_read_completion(t_io_uring *ring, t_io_uring_cqe *cqe)
{
	t_u32a	head;
	t_u32a	tail;
	t_u32a	mask;

	head = atomic_load_explicit(ring->cq_head, xft_relaxed);
	tail = atomic_load_explicit(ring->cq_tail, xft_acquire);
	if (__builtin_expect(head == tail, 0))
		return ((t_result){.err = xft_err_retry});
	mask = ring->cq_mask;
	*cqe = ring->cqes[head & mask];
	atomic_store_explicit(ring->cq_head, head + 1, xft_release);
	return ((t_result){.ok = OK});
}
