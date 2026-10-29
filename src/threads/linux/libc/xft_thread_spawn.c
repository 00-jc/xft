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

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC
#  include <pthread.h>

__attribute__((__nonnull__(1)))
static t_any	xft__thread_entry(t_any arg)
{
	t_thread_start *__restrict__ const	start = arg;
	const t_thread_func					fn = start->fn;
	const t_any							argument = start->argument;

	xft_mutex_unlock(&start->started);
	fn(argument);
	return (nullptr);
}

__attribute__((__flatten__, __nonnull__(1)))
t_result	xft_thread_spawn(t_thread *__restrict__ const thread,
	t_sysinfo sysinfo, t_thread_opts opts)
{
	t_thread_start	start;
	pthread_attr_t	attr;
	pthread_t		tid;
	int				ret;

	(void)sysinfo;
	start.fn = opts.fn;
	start.argument = opts.argument;
	xft_mutex_init(&start.started);
	xft_mutex_lock(&start.started, xft_lock_fast);
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, opts.stack_size);
	ret = pthread_create(&tid, &attr, xft__thread_entry, &start);
	pthread_attr_destroy(&attr);
	if (__builtin_expect(ret != 0, 0))
		return (KO);
	xft_mutex_lock(&start.started, xft_lock_fast);
	thread->handle = (t_thread_id)tid;
	return (OK);
}

# endif

#endif
