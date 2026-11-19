/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_flush_submissions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/linux/uring.h>
#include <stdatomic.h>

__attribute__((__nonnull__(1)))
t_result	xft_flush_submissions(t_io_uring *ring)
{
	t_u32a	head;
	t_u32a	tail;
	int		submitted;

	tail = ring->sq_local_tail;
	atomic_store_explicit(ring->sq_tail, tail, xft_release);
	head = atomic_load_explicit(ring->sq_head, xft_relaxed);
	if (head == tail)
		return ((t_result){.ok = OK});
	return (xft_io_uring_enter((int)ring->fd,
			(t_io_uring_enter){.to_submit = tail - head}, &submitted));
}
