/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer_test_fifo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/atomics/ring_buffer/ring_buffer_test.h"

// items[p & 15] is the payload for queue position p
static void	ring_buffer_push(t_ring_buffer *__restrict__ const rb,
	t_u8 *__restrict__ const items, t_u32a *__restrict__ const in)
{
	xft_pin_invariant_msg(xft_ring_buffer_submit(rb, &items[*in & 15]) == OK,
		xft_fatptr((t_u8 *)"ring buffer: submit",
			sizeof("ring buffer: submit") - 1));
	*in += 1;
}

static void	ring_buffer_pop(t_ring_buffer *__restrict__ const rb,
	t_u8 *__restrict__ const items, t_u32a *__restrict__ const out)
{
	xft_pin_invariant_msg(xft_ring_buffer_steal(rb) == &items[*out & 15],
		xft_fatptr((t_u8 *)"ring buffer: steal order",
			sizeof("ring buffer: steal order") - 1));
	*out += 1;
}

static void	ring_buffer_empty(t_ring_buffer *__restrict__ const rb)
{
	xft_pin_invariant_msg(xft_ring_buffer_steal(rb) == nullptr,
		xft_fatptr((t_u8 *)"ring buffer: steal empty",
			sizeof("ring buffer: steal empty") - 1));
	xft_pin_invariant_msg(rb->head == rb->tail,
		xft_fatptr((t_u8 *)"ring buffer: drained cursors",
			sizeof("ring buffer: drained cursors") - 1));
}

static void	ring_buffer_lap(t_ring_buffer *__restrict__ const rb,
	t_u8 *__restrict__ const items, t_u32a *__restrict__ const in,
	t_u32a *__restrict__ const out)
{
	t_u32a	i;

	i = 0;
	while (i++ < rb->size)
		ring_buffer_push(rb, items, in);
	xft_pin_invariant_msg(xft_ring_buffer_submit(rb, items) == KO,
		xft_fatptr((t_u8 *)"ring buffer: submit full",
			sizeof("ring buffer: submit full") - 1));
	while (*out != *in)
		ring_buffer_pop(rb, items, out);
	ring_buffer_empty(rb);
}

void	test_ring_buffer_fifo(void)
{
	const t_allocator	alloc = xft_page_allocator();
	t_ring_buffer		rb;
	t_u8				items[16];
	t_u32a				in;
	t_u32a				out;

	rb = xft_new_ring_buffer(alloc, 5);
	ring_buffer_empty(&rb);
	in = 0;
	out = 0;
	while (in < 3 * rb.size)
		ring_buffer_lap(&rb, items, &in, &out);
	while (in - out + 3 <= rb.size)
	{
		ring_buffer_push(&rb, items, &in);
		ring_buffer_push(&rb, items, &in);
		ring_buffer_push(&rb, items, &in);
		ring_buffer_pop(&rb, items, &out);
		ring_buffer_pop(&rb, items, &out);
	}
	while (out != in)
		ring_buffer_pop(&rb, items, &out);
	ring_buffer_empty(&rb);
	xft_destroy_ring_buffer(alloc, &rb);
}
