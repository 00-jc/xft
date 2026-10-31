/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_ring_buffer_backoff_utils.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

#ifdef __linux__

static void	rb_backoff_stealer(t_any arg)
{
	t_rb_backoff_test *__restrict__ const	s = arg;
	t_u32a									i;

	i = atomic_fetch_add_explicit(&s->started, 1, xft_relaxed);
	atomic_store_explicit(&s->got[i], xft_ring_buffer_steal(&s->rb),
		xft_relaxed);
	atomic_fetch_add_explicit(&s->returned, 1, xft_release);
}

static void	rb_backoff_submitter(t_any arg)
{
	t_rb_backoff_test *__restrict__ const	s = arg;
	t_u32a									i;

	i = atomic_fetch_add_explicit(&s->started, 1, xft_relaxed);
	xft_pin_invariant_msg(xft_ring_buffer_submit(&s->rb, &s->items[i]) == OK,
		xft_fatptr((t_u8 *)"ring buffer: backoff submit",
			sizeof("ring buffer: backoff submit") - 1));
	atomic_fetch_add_explicit(&s->returned, 1, xft_release);
}

// every thread is spinning on the in-flight slot when this returns
void	thread_rb_backoff_start(t_rb_backoff_test *__restrict__ const s,
	t_sysinfo sysinfo, const bool steal)
{
	t_thread_opts	opts;
	t_u32a			i;

	atomic_store_explicit(&s->started, 0, xft_relaxed);
	atomic_store_explicit(&s->returned, 0, xft_relaxed);
	opts.fn = rb_backoff_submitter;
	if (steal)
		opts.fn = rb_backoff_stealer;
	opts.stack_size = XFT_THREAD_STACKSIZE;
	opts.argument = s;
	i = 0;
	while (i < RB_BACKOFF_THREADS)
		xft_pin_invariant_msg(xft_thread_spawn(&s->threads[i++], sysinfo,
				opts) == OK, xft_fatptr((t_u8 *)"thread spawn",
				sizeof("thread spawn") - 1));
	while (atomic_load_explicit(&s->started, xft_acquire) < RB_BACKOFF_THREADS)
		xft_backoff(1);
	xft_backoff(RB_BACKOFF_DELAY);
	xft_pin_invariant_msg(atomic_load_explicit(&s->returned, xft_acquire) == 0,
		xft_fatptr((t_u8 *)"ring buffer: backoff in flight",
			sizeof("ring buffer: backoff in flight") - 1));
}

// slots must hold each of items[0, RB_BACKOFF_THREADS) exactly once
void	thread_rb_backoff_finish(t_rb_backoff_test *__restrict__ const s,
	t_atomicptr *__restrict__ const slots)
{
	t_u8	*p;
	t_u32a	seen;
	t_u32a	i;

	i = 0;
	while (i < RB_BACKOFF_THREADS)
		xft_thread_join(&s->threads[i++]);
	xft_pin_invariant_msg(atomic_load_explicit(&s->returned, xft_acquire)
		== RB_BACKOFF_THREADS, xft_fatptr((t_u8 *)"ring buffer: backoff join",
			sizeof("ring buffer: backoff join") - 1));
	seen = 0;
	i = 0;
	while (i < RB_BACKOFF_THREADS)
	{
		p = atomic_load_explicit(&slots[i++], xft_relaxed);
		xft_pin_invariant_msg(p >= s->items
			&& p < s->items + RB_BACKOFF_THREADS,
			xft_fatptr((t_u8 *)"ring buffer: backoff payload",
				sizeof("ring buffer: backoff payload") - 1));
		seen |= 1u << (p - s->items);
	}
	xft_pin_invariant_msg(seen == (1u << RB_BACKOFF_THREADS) - 1,
		xft_fatptr((t_u8 *)"ring buffer: backoff once",
			sizeof("ring buffer: backoff once") - 1));
}

#endif
