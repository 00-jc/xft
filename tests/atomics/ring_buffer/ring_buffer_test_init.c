/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer_test_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/atomics/ring_buffer/ring_buffer_test.h"

static void	ring_buffer_init_size(t_u32a min_size, t_u32a expect)
{
	const t_allocator	alloc = xft_page_allocator();
	t_ring_buffer		rb;
	t_u32a				i;

	rb = xft_new_ring_buffer(alloc, min_size);
	xft_pin_invariant_msg(rb.memory != nullptr && rb.size == expect,
		xft_fatptr((t_u8 *)"ring buffer: init size",
			sizeof("ring buffer: init size") - 1));
	xft_pin_invariant_msg(rb.alloc_bytes >= expect * sizeof(t_atomicptr),
		xft_fatptr((t_u8 *)"ring buffer: init bytes",
			sizeof("ring buffer: init bytes") - 1));
	xft_pin_invariant_msg(rb.head == 0 && rb.tail == 0,
		xft_fatptr((t_u8 *)"ring buffer: init cursors",
			sizeof("ring buffer: init cursors") - 1));
	i = 0;
	while (i < rb.size)
		xft_pin_invariant_msg(atomic_load(&rb.memory[i++]) == nullptr,
			xft_fatptr((t_u8 *)"ring buffer: init zeroed",
				sizeof("ring buffer: init zeroed") - 1));
	xft_destroy_ring_buffer(alloc, &rb);
}

static void	ring_buffer_init_reject(t_u32a min_size)
{
	t_ring_buffer	rb;

	rb = xft_new_ring_buffer(xft_page_allocator(), min_size);
	xft_pin_invariant_msg(rb.memory == nullptr && rb.size == 0,
		xft_fatptr((t_u8 *)"ring buffer: init reject",
			sizeof("ring buffer: init reject") - 1));
}

void	test_ring_buffer_init(void)
{
	ring_buffer_init_size(1, 1);
	ring_buffer_init_size(2, 2);
	ring_buffer_init_size(5, 8);
	ring_buffer_init_size(8, 8);
	ring_buffer_init_size(1000, 1024);
	ring_buffer_init_reject(0);
	ring_buffer_init_reject((1u << 31) + 1);
	ring_buffer_init_reject(0xFFFFFFFF);
}
