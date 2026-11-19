/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_new_io_uring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft/types/xft_p_syscalls_types.h"
#include <xft/linux/uring.h>
#include <xft/xft_p_syscalls.h>
#include <xft/mem.h>

__attribute__((__nonnull__(1, 4)))
static t_result	map_ring(t_io_uring *r, t_size s, t_u64a offset, t_any *out)
{
	t_any	ptr;
	t_any	sq;
	t_any	cq;

	ptr = xft_fmap_at(s, xft_prot_read | xft_prot_write,
			xft_map_shared | xft_map_populate,
			(const t_u64a [2]){(t_u64a)r->fd, offset});
	if (__builtin_expect(!xft_map_failed(ptr).ok, 1))
	{
		*out = ptr;
		return ((t_result){.ok = OK});
	}
	sq = r->sq_ring;
	cq = r->cq_ring;
	if (cq != nullptr && cq != sq)
		xft_munmap(cq, r->cq_ring_size);
	if (sq != nullptr)
		xft_munmap(sq, r->sq_ring_size);
	xft_close(r->fd);
	xft_memset(r, 0, sizeof(*r));
	r->fd = -1;
	*out = nullptr;
	return ((t_result){.ok = KO, .err = -(t_uptr)ptr});
}

__attribute__((__nonnull__(1, 2)))
static void	ring_sizes(t_io_uring *r, const t_io_uring_params *p)
{
	t_size	sq;
	t_size	cq;

	sq = p->sq_entries * sizeof(t_u32);
	cq = p->cq_entries * sizeof(t_io_uring_cqe);
	sq += p->sq_off.array;
	cq += p->cq_off.cqes;
	if (p->features & IORING_FEAT_SINGLE_MMAP)
	{
		sq = xft_max_s(sq, cq);
		cq = sq;
	}
	r->sq_ring_size = sq;
	r->cq_ring_size = cq;
	r->sqes_size = p->sq_entries * sizeof(t_io_uring_sqe);
	r->features = p->features;
}

__attribute__((__nonnull__(1)))
static t_result	map_rings(t_io_uring *r)
{
	t_result	res;
	t_any		ring;

	res = map_ring(r, r->sq_ring_size, IORING_OFF_SQ_RING, &ring);
	if (__builtin_expect(!res.ok, 0))
		return (res);
	r->sq_ring = ring;
	if (!(r->features & IORING_FEAT_SINGLE_MMAP))
		res = map_ring(r, r->cq_ring_size, IORING_OFF_CQ_RING, &ring);
	if (__builtin_expect(!res.ok, 0))
		return (res);
	r->cq_ring = ring;
	res = map_ring(r, r->sqes_size, IORING_OFF_SQES, &ring);
	r->sqes = ring;
	return (res);
}

__attribute__((__nonnull__(1, 2)))
static void	fill_ring(t_io_uring *r, const t_io_uring_params *p)
{
	t_u8	*sq;
	t_u8	*cq;
	t_u32	i;

	sq = r->sq_ring;
	cq = r->cq_ring;
	r->sq_head = (t_atomic32 *)(sq + p->sq_off.head);
	r->sq_tail = (t_atomic32 *)(sq + p->sq_off.tail);
	r->sq_flags = (t_atomic32 *)(sq + p->sq_off.flags);
	r->sq_array = (t_u32 *)(sq + p->sq_off.array);
	r->sq_mask = *(t_u32 *)(sq + p->sq_off.ring_mask);
	r->sq_entries = p->sq_entries;
	r->cq_head = (t_atomic32 *)(cq + p->cq_off.head);
	r->cq_tail = (t_atomic32 *)(cq + p->cq_off.tail);
	r->cqes = (t_io_uring_cqe *)(cq + p->cq_off.cqes);
	r->cq_mask = *(t_u32 *)(cq + p->cq_off.ring_mask);
	r->cq_entries = p->cq_entries;
	i = 0;
	while (i < p->sq_entries)
	{
		r->sq_array[i] = i;
		i++;
	}
}

__attribute__((__nonnull__(1), __flatten__))
t_result	xft_new_io_uring(t_io_uring *__restrict__ const
	ring)
{
	t_io_uring_params	p;
	t_result			r;
	int					fd;

	xft_memset(&p, 0, sizeof(p));
	xft_memset(ring, 0, sizeof(*ring));
	r = xft_io_uring_setup(512, &p, &fd);
	if (__builtin_expect(!r.ok, 0))
	{
		ring->fd = -1;
		return (r);
	}
	ring->fd = (t_fd)fd;
	ring_sizes(ring, &p);
	r = map_rings(ring);
	if (__builtin_expect(r.ok, 1))
		fill_ring(ring, &p);
	return (r);
}
