/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_ring_buffer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

#ifdef __linux__

static void	ring_buffer_producer(t_any arg)
{
	t_ring_buffer_test *__restrict__ const	s = arg;
	t_u32a									i;

	i = atomic_fetch_add_explicit(&s->next, 1, xft_relaxed);
	while (i < RB_TEST_ITEMS)
	{
		s->items[i] = (t_u8)i;
		while (xft_ring_buffer_submit(&s->rb, &s->items[i]) == KO)
			atomic_fetch_add_explicit(&s->full, 1, xft_relaxed);
		i = atomic_fetch_add_explicit(&s->next, 1, xft_relaxed);
	}
	atomic_fetch_add_explicit(&s->done, 1, xft_release);
}

static void	ring_buffer_consumer(t_any arg)
{
	t_ring_buffer_test *__restrict__ const	s = arg;
	t_u8									*slot;
	bool									done;

	while (true)
	{
		done = atomic_load_explicit(&s->done, xft_acquire)
			== RB_TEST_THREADS / 2;
		slot = xft_ring_buffer_steal(&s->rb);
		if (slot == nullptr && done)
			break ;
		if (slot == nullptr)
			continue ;
		xft_pin_invariant_msg(*slot == (t_u8)(slot - s->items),
			xft_fatptr((t_u8 *)"ring buffer: payload",
				sizeof("ring buffer: payload") - 1));
		atomic_fetch_add_explicit(&s->seen[slot - s->items], 1, xft_relaxed);
		atomic_fetch_add_explicit(&s->consumed, 1, xft_release);
	}
}

static void	ring_buffer_spawn(t_thread *__restrict__ const thread,
	t_sysinfo sysinfo, t_ring_buffer_test *__restrict__ const s,
	t_thread_func fn)
{
	t_thread_opts	opts;

	opts.fn = fn;
	opts.stack_size = XFT_THREAD_STACKSIZE;
	opts.argument = s;
	xft_pin_invariant_msg(xft_thread_spawn(thread, sysinfo, opts) == OK,
		xft_fatptr((t_u8 *)"thread spawn", sizeof("thread spawn") - 1));
}

static void	ring_buffer_check(t_ring_buffer_test *__restrict__ const s)
{
	t_u32a	i;

	xft_pin_invariant_msg(atomic_load_explicit(&s->consumed, xft_acquire)
		== RB_TEST_ITEMS && s->rb.head == RB_TEST_ITEMS
		&& s->rb.tail == RB_TEST_ITEMS,
		xft_fatptr((t_u8 *)"ring buffer: consumed",
			sizeof("ring buffer: consumed") - 1));
	i = 0;
	while (i < RB_TEST_ITEMS)
		xft_pin_invariant_msg(atomic_load_explicit(&s->seen[i++],
				xft_relaxed) == 1,
			xft_fatptr((t_u8 *)"ring buffer: seen once",
				sizeof("ring buffer: seen once") - 1));
}

void	test_thread_ring_buffer(t_sysinfo sysinfo)
{
	const t_allocator	alloc = xft_page_allocator();
	t_ring_buffer_test	s;
	t_thread			threads[RB_TEST_THREADS];
	t_u32a				i;

	xft_bzero(&s, sizeof(s));
	s.rb = xft_new_ring_buffer(alloc, RB_TEST_SIZE);
	xft_pin_invariant_msg(s.rb.memory != nullptr,
		xft_fatptr((t_u8 *)"ring buffer: new", sizeof("ring buffer: new") - 1));
	i = 0;
	while (i < RB_TEST_THREADS)
	{
		if (i & 1)
			ring_buffer_spawn(&threads[i], sysinfo, &s, ring_buffer_consumer);
		else
			ring_buffer_spawn(&threads[i], sysinfo, &s, ring_buffer_producer);
		i++;
	}
	i = 0;
	while (i < RB_TEST_THREADS)
		xft_thread_join(&threads[i++]);
	ring_buffer_check(&s);
	xft_destroy_ring_buffer(alloc, &s.rb);
}

#endif
