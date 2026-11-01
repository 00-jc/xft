/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 15:49:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/31 15:52:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include <xft/primitives.h>
# include <xft/alloc.h>
# include <xft/rt.h>
# include <xft/types/thread_types.h>

# if !defined(_WIN32) && !defined(XFT_REQUIRE_LIBC)

void			xft_thread_destroy(\
				t_thread_instance *__restrict__ const instance)\
				__attribute__((__nonnull__(1), __noreturn__));

# endif

t_result		xft_thread_spawn(t_thread *__restrict__ const thread,\
				t_sysinfo sysinfo, t_thread_opts opts)\
				__attribute__((__nonnull__(1)));

void			xft_thread_join(t_thread *__restrict__ const thread)\
				__attribute__((__nonnull__(1)));

void			xft_thread_detach(t_thread *__restrict__ const thread)\
				__attribute__((__nonnull__(1)));

t_thread_id		xft_thread_id(const t_thread *__restrict__ const thread)\
				__attribute__((__nonnull__(1)));

t_thread_opts	xft_threadpool_default(void);

t_result		xft_threadpool_init(t_allocator allocator,\
				const t_sysinfo info, t_thread_opts opts,\
				t_threadpool *__restrict__ const tp)\
				__attribute__((__nonnull__(4)));

void			xft_threadpool_destroy(t_allocator allocator,\
				t_threadpool *__restrict__ const tp)\
				__attribute__((__nonnull__(2)));

void			xft_threadpool_cancel(t_allocator allocator,\
				t_threadpool *__restrict__ const tp)\
				__attribute__((__nonnull__(2)));

void			xft_threadpool_submit(t_threadpool *__restrict__ const tp,\
				t_thread_task *__restrict__ const task, t_size alloc_task)\
				__attribute__((__nonnull__(1, 2)));

void			xft_threadpool_submit_fair(t_threadpool *__restrict__ const tp,\
				t_thread_task *__restrict__ const tasks, t_size alloc_task,\
				t_size n_tasks)\
				__attribute__((__nonnull__(1, 2)));

void			xft_threadpool_wait_task(t_thread_task *__restrict__ const task)\
				__attribute__((__nonnull__(1)));

#endif
