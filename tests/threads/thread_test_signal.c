/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 22:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"
#include <stdint.h>

static void	thread_futex_fn(t_any arg)
{
	t_signal_test *__restrict__ const	s = arg;

	while (atomic_load_explicit(&s->wake, xft_acquire) == 0)
		xft_futex_wait(&s->wake, 0);
	atomic_fetch_add_explicit(&s->progress, 1, xft_release);
}

static void	thread_test_broadcast(t_sysinfo sysinfo,
	t_signal_test *__restrict__ const s)
{
	t_thread	threads[2];

	thread_signal_spawn(&threads[0], sysinfo, s, thread_futex_fn);
	thread_signal_spawn(&threads[1], sysinfo, s, thread_futex_fn);
	atomic_store_explicit(&s->wake, 1, xft_release);
	xft_futex_wake(&s->wake, INT32_MAX);
	xft_thread_join(&threads[0]);
	xft_thread_join(&threads[1]);
	xft_pin_invariant_msg(atomic_load_explicit(&s->progress, xft_acquire) == 2,
		xft_fatptr((t_u8 *)"futex broadcast",
			sizeof("futex broadcast") - 1));
}

void	test_thread_signal(t_sysinfo sysinfo)
{
	t_signal_test	s;

	atomic_init(&s.wake, 0);
	atomic_init(&s.go, 0);
	atomic_init(&s.progress, 0);
	atomic_init(&s.ready, 0);
	s.rounds = 8;
	thread_test_broadcast(sysinfo, &s);
	thread_signal_rounds(sysinfo, &s, 2, true);
	thread_signal_rounds(sysinfo, &s, 1, false);
}
