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

#ifdef __linux__

static void	thread_tls_fn(t_any arg)
{
	static _Thread_local t_u64	tdata = 7;
	static _Thread_local t_u64	tbss;
	t_u64 *__restrict__ const	out = arg;

	out[0] = tdata;
	out[1] = tbss;
	tdata = 1;
	tbss = 2;
	out[2] = (t_u64) & tdata;
}

static void	thread_tls_check(const t_u64 *__restrict__ const out)
{
	xft_pin_invariant_msg(out[0] == 7,
		xft_fatptr((t_u8 *)"thread tdata", sizeof("thread tdata") - 1));
	xft_pin_invariant_msg(out[1] == 0,
		xft_fatptr((t_u8 *)"thread tbss", sizeof("thread tbss") - 1));
}

void	test_thread_tls(t_sysinfo sysinfo)
{
	t_thread		threads[2];
	t_thread_opts	opts;
	t_u64			out[2][3];

	opts.fn = thread_tls_fn;
	opts.stack_size = XFT_THREAD_STACKSIZE;
	opts.argument = out[0];
	xft_pin_invariant_msg(xft_thread_spawn(&threads[0], sysinfo, opts) == OK,
		xft_fatptr((t_u8 *)"thread spawn", sizeof("thread spawn") - 1));
	opts.argument = out[1];
	xft_pin_invariant_msg(xft_thread_spawn(&threads[1], sysinfo, opts) == OK,
		xft_fatptr((t_u8 *)"thread spawn", sizeof("thread spawn") - 1));
	xft_thread_join(&threads[0]);
	xft_thread_join(&threads[1]);
	thread_tls_check(out[0]);
	thread_tls_check(out[1]);
	xft_pin_invariant_msg(out[0][2] != out[1][2],
		xft_fatptr((t_u8 *)"thread tls shared", sizeof("thread tls shared")
			- 1));
}

#endif
