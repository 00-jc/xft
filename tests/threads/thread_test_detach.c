/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_detach.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

static void	thread_detach_wait_exit(const t_thread *__restrict__ const thread)
{
	(void)thread;
}

# else

static void	thread_detach_wait_exit(const t_thread *__restrict__ const thread)
{
	while (xft_thread_id(thread) != 0)
		__atomic_thread_fence(xft_seq_cst);
}

# endif

void	test_thread_detach(t_sysinfo sysinfo)
{
	t_thread	thread;
	t_u32a		flags[2];

	thread_detach_spawn(&thread, sysinfo, flags);
	xft_thread_detach(&thread);
	thread_detach_run(flags);
	thread_detach_spawn(&thread, sysinfo, flags);
	thread_detach_run(flags);
	thread_detach_wait_exit(&thread);
	xft_thread_detach(&thread);
}

#endif
