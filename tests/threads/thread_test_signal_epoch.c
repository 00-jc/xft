/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_signal_epoch.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

#ifdef __linux__

static void	thread_signal_fn(t_any arg)
{
	t_signal_test *__restrict__ const	s = arg;
	t_u32a								epoch;
	t_u32a								round;

	round = 0;
	while (round++ < s->rounds)
	{
		epoch = xft_signal_epoch(&s->go);
		atomic_fetch_add_explicit(&s->ready, 1, xft_release);
		xft_wait_for_signal(&s->go, epoch);
		xft_pin_invariant_msg(xft_signal_epoch(&s->go) != epoch,
			xft_fatptr((t_u8 *)"signal without send",
				sizeof("signal without send") - 1));
		atomic_fetch_add_explicit(&s->progress, 1, xft_release);
	}
}

void	thread_signal_spawn(t_thread *__restrict__ const thread,
	t_sysinfo sysinfo, t_signal_test *__restrict__ const s, t_thread_func fn)
{
	t_thread_opts	opts;

	opts.fn = fn;
	opts.stack_size = XFT_THREAD_STACKSIZE;
	opts.argument = s;
	xft_pin_invariant_msg(xft_thread_spawn(thread, sysinfo, opts) == OK,
		xft_fatptr((t_u8 *)"thread spawn", sizeof("thread spawn") - 1));
}

// one send per round: every waiter took its epoch before the send
void	thread_signal_rounds(t_sysinfo sysinfo,
	t_signal_test *__restrict__ const s, const t_u32a n, const bool for_all)
{
	t_thread	threads[2];
	t_u32a		round;
	t_u32a		i;

	atomic_store_explicit(&s->ready, 0, xft_relaxed);
	atomic_store_explicit(&s->progress, 0, xft_relaxed);
	i = 0;
	while (i < n)
		thread_signal_spawn(&threads[i++], sysinfo, s, thread_signal_fn);
	round = 0;
	while (round++ < s->rounds)
	{
		while (atomic_load_explicit(&s->ready, xft_acquire) < round * n)
			xft_backoff(1);
		if (for_all)
			xft_send_signal_for_all(&s->go);
		else
			xft_send_signal(&s->go);
	}
	i = 0;
	while (i < n)
		xft_thread_join(&threads[i++]);
	xft_pin_invariant_msg(atomic_load_explicit(&s->progress, xft_acquire)
		== s->rounds * n, xft_fatptr((t_u8 *)"signal rounds",
			sizeof("signal rounds") - 1));
}

#endif
