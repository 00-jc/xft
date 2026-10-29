/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_detach_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"
#include <xft/atomics.h>

#ifdef __linux__

static void	thread_detach_fn(t_any arg)
{
	t_u32a *__restrict__ const	flags = arg;

	while (__atomic_load_n(&flags[0], xft_acquire) == 0)
		xft_futex_wait((t_any)&flags[0], 0);
	__atomic_store_n(&flags[1], 1, xft_release);
	xft_futex_wake((t_any)&flags[1], 1);
}

void	thread_detach_run(t_u32a *__restrict__ const flags)
{
	__atomic_store_n(&flags[0], 1, xft_release);
	xft_futex_wake((t_any)&flags[0], 1);
	while (__atomic_load_n(&flags[1], xft_acquire) == 0)
		xft_futex_wait((t_any)&flags[1], 0);
}

void	thread_detach_spawn(t_thread *__restrict__ const thread,
	t_sysinfo sysinfo, t_u32a *__restrict__ const flags)
{
	t_thread_opts	opts;

	flags[0] = 0;
	flags[1] = 0;
	opts.fn = thread_detach_fn;
	opts.stack_size = XFT_THREAD_STACKSIZE;
	opts.argument = flags;
	xft_pin_invariant_msg(xft_thread_spawn(thread, sysinfo, opts) == OK,
		xft_fatptr((t_u8 *)"thread spawn", sizeof("thread spawn") - 1));
}

#endif
