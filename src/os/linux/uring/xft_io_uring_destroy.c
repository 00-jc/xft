/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_io_uring_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/linux/uring.h>
#include <xft/xft_p_syscalls.h>
#include <xft/mem.h>

__attribute__((__nonnull__(1)))
void	xft_io_uring_destroy(t_io_uring *ring)
{
	t_any	sq;
	t_any	cq;
	t_any	sqes;

	sq = ring->sq_ring;
	cq = ring->cq_ring;
	sqes = ring->sqes;
	if (sqes != nullptr)
		xft_munmap(sqes, ring->sqes_size);
	if (cq != nullptr && cq != sq)
		xft_munmap(cq, ring->cq_ring_size);
	if (sq != nullptr)
		xft_munmap(sq, ring->sq_ring_size);
	xft_close(ring->fd);
	xft_memset(ring, 0, sizeof(*ring));
	ring->fd = -1;
}
