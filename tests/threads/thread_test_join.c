/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

#ifdef __linux__

static void	thread_join_fn(t_any arg)
{
	__atomic_store_n((t_u32a *)arg, 42, __ATOMIC_RELEASE);
}

void	test_thread_join(t_sysinfo sysinfo)
{
	t_thread		thread;
	t_thread_opts	opts;
	t_u32a			value;

	value = 0;
	opts.fn = thread_join_fn;
	opts.stack_size = XFT_THREAD_STACKSIZE;
	opts.argument = &value;
	xft_pin_invariant_msg(xft_thread_spawn(&thread, sysinfo, opts) == OK,
		xft_fatptr((t_u8 *)"thread spawn", sizeof("thread spawn") - 1));
	xft_thread_join(&thread);
	xft_pin_invariant_msg(value == 42,
		xft_fatptr((t_u8 *)"thread join value",
			sizeof("thread join value") - 1));
}

#endif
