/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_thread_spawn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/threads.h>
#include <xft/atomics.h>
#include <xft/xft_p_thread_start.h>

#ifdef _WIN32

__attribute__((__nonnull__(1)))
static DWORD WINAPI	xft__thread_entry(LPVOID arg)
{
	t_thread_start *__restrict__ const	start = arg;
	const t_thread_func					fn = start->fn;
	const t_any							argument = start->argument;

	xft_mutex_unlock(&start->started);
	fn(argument);
	return (0);
}

__attribute__((__flatten__, __nonnull__(1)))
t_result	xft_thread_spawn(t_thread *__restrict__ const thread,
	t_sysinfo sysinfo, t_thread_opts opts)
{
	t_thread_start	start;
	HANDLE			handle;

	(void)sysinfo;
	start.fn = opts.fn;
	start.argument = opts.argument;
	xft_mutex_init(&start.started);
	xft_mutex_lock(&start.started, xft_lock_fast);
	handle = CreateThread(nullptr, opts.stack_size, xft__thread_entry,
			&start, STACK_SIZE_PARAM_IS_A_RESERVATION, nullptr);
	if (__builtin_expect(handle == nullptr, 0))
		return (KO);
	xft_mutex_lock(&start.started, xft_lock_fast);
	thread->handle = (t_thread_id)handle;
	return (OK);
}

#endif
