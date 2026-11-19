/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_queue_submission.c                             :+:      :+:    :+:   */
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
t_result	xft_queue_submission(t_io_uring *ring, const t_io_uring_sqe *sqe)
{
	t_u32a	head;
	t_u32a	tail;
	t_u32a	entries;
	t_u32a	mask;

	head = atomic_load_explicit(ring->sq_head, xft_acquire);
	tail = ring->sq_local_tail;
	entries = ring->sq_entries;
	if (__builtin_expect(tail - head >= entries, 0))
		return ((t_result){.err = xft_err_nospace});
	mask = ring->sq_mask;
	ring->sqes[tail & mask] = *sqe;
	ring->sq_local_tail = tail + 1;
	return ((t_result){.ok = OK});
}
