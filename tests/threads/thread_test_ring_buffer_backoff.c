/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_ring_buffer_backoff.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

#ifdef __linux__

// positions [0, RB_BACKOFF_THREADS) are claimed by a producer that has not
// stored yet, so every stealer backs off on slot 0 until the stores land
static void	rb_backoff_steal(t_sysinfo sysinfo,
	t_rb_backoff_test *__restrict__ const s)
{
	t_u32a	i;

	atomic_store_explicit(&s->rb.tail, RB_BACKOFF_THREADS, xft_relaxed);
	thread_rb_backoff_start(s, sysinfo, true);
	i = 0;
	while (i < RB_BACKOFF_THREADS)
	{
		atomic_store_explicit(&s->rb.memory[i], &s->items[i], xft_release);
		i++;
	}
	thread_rb_backoff_finish(s, s->got);
	xft_pin_invariant_msg(s->rb.head == RB_BACKOFF_THREADS,
		xft_fatptr((t_u8 *)"ring buffer: backoff steal head",
			sizeof("ring buffer: backoff steal head") - 1));
	i = 0;
	while (i < RB_BACKOFF_THREADS)
		xft_pin_invariant_msg(atomic_load(&s->rb.memory[i++]) == nullptr,
			xft_fatptr((t_u8 *)"ring buffer: backoff steal clear",
				sizeof("ring buffer: backoff steal clear") - 1));
}

// positions [0, RB_BACKOFF_THREADS) are claimed by a consumer that has not
// cleared yet, so every submitter backs off on slot 0 until the clears land
static void	rb_backoff_submit(t_sysinfo sysinfo,
	t_rb_backoff_test *__restrict__ const s)
{
	t_u8 *__restrict__ const	old = &s->items[RB_BACKOFF_THREADS];
	t_u32a						i;

	i = 0;
	while (i < RB_BACKOFF_SIZE)
		atomic_store_explicit(&s->rb.memory[i++], old, xft_relaxed);
	atomic_store_explicit(&s->rb.head, RB_BACKOFF_THREADS, xft_relaxed);
	atomic_store_explicit(&s->rb.tail, RB_BACKOFF_SIZE, xft_relaxed);
	thread_rb_backoff_start(s, sysinfo, false);
	i = 0;
	while (i < RB_BACKOFF_THREADS)
		atomic_store_explicit(&s->rb.memory[i++], nullptr, xft_release);
	thread_rb_backoff_finish(s, s->rb.memory);
	xft_pin_invariant_msg(s->rb.tail == RB_BACKOFF_SIZE + RB_BACKOFF_THREADS
		&& atomic_load(&s->rb.memory[RB_BACKOFF_THREADS]) == old,
		xft_fatptr((t_u8 *)"ring buffer: backoff submit tail",
			sizeof("ring buffer: backoff submit tail") - 1));
}

void	test_thread_ring_buffer_backoff(t_sysinfo sysinfo)
{
	const t_allocator	alloc = xft_page_allocator();
	t_rb_backoff_test	s;

	xft_bzero(&s, sizeof(s));
	s.rb = xft_new_ring_buffer(alloc, RB_BACKOFF_SIZE);
	xft_pin_invariant_msg(s.rb.memory != nullptr
		&& s.rb.size == RB_BACKOFF_SIZE,
		xft_fatptr((t_u8 *)"ring buffer: new", sizeof("ring buffer: new") - 1));
	rb_backoff_steal(sysinfo, &s);
	rb_backoff_submit(sysinfo, &s);
	xft_destroy_ring_buffer(alloc, &s.rb);
}

#endif
