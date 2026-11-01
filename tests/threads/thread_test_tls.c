/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_tls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

static void	thread_tls_fn(t_any arg)
{
	static _Thread_local t_u64	tdata = 7;
	static _Thread_local t_u64	tbss;
	t_u64a *__restrict__ const	out = arg;

	out[0] = tdata;
	out[1] = tbss;
	tdata = 1;
	tbss = 2;
	out[2] = (t_u64) & tdata;
}

static void	thread_tls_check(const t_u64a *__restrict__ const out)
{
	xft_pin_invariant_msg(out[0] == 7,
		xft_fatptr((t_u8 *)"thread tdata", sizeof("thread tdata") - 1));
	xft_pin_invariant_msg(out[1] == 0,
		xft_fatptr((t_u8 *)"thread tbss", sizeof("thread tbss") - 1));
}

// stays alive until main has compared every live thread's tls address,
// a finished thread's tls block can be reused by the next one
static void	thread_tls_hold(t_any arg)
{
	t_u64a *__restrict__ const	out = arg;

	thread_tls_fn(out);
	__atomic_store_n(&out[3], 1, xft_release);
	while (__atomic_load_n(&out[3], xft_acquire) != 2)
		xft_backoff(1);
}

static void	thread_tls_spawn(t_thread *__restrict__ const thread,
	t_sysinfo sysinfo, t_u64a *__restrict__ const out)
{
	t_thread_opts	opts;

	out[3] = 0;
	opts.fn = thread_tls_hold;
	opts.stack_size = XFT_THREAD_STACKSIZE;
	opts.argument = out;
	xft_pin_invariant_msg(xft_thread_spawn(thread, sysinfo, opts) == OK,
		xft_fatptr((t_u8 *)"thread spawn", sizeof("thread spawn") - 1));
}

void	test_thread_tls(t_sysinfo sysinfo)
{
	t_thread	threads[2];
	t_u64a		out[3][4];

	thread_tls_fn(out[2]);
	thread_tls_check(out[2]);
	thread_tls_spawn(&threads[0], sysinfo, out[0]);
	thread_tls_spawn(&threads[1], sysinfo, out[1]);
	while (__atomic_load_n(&out[0][3], xft_acquire) != 1
		|| __atomic_load_n(&out[1][3], xft_acquire) != 1)
		xft_backoff(1);
	xft_pin_invariant_msg(out[0][2] != out[1][2] && out[0][2] != out[2][2]
		&& out[1][2] != out[2][2], xft_fatptr((t_u8 *)"thread tls shared",
			sizeof("thread tls shared") - 1));
	__atomic_store_n(&out[0][3], 2, xft_release);
	__atomic_store_n(&out[1][3], 2, xft_release);
	xft_thread_join(&threads[0]);
	xft_thread_join(&threads[1]);
	thread_tls_check(out[0]);
	thread_tls_check(out[1]);
}
