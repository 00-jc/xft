/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threaded_async.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_async.h>
#include <xft/xft_p_threadpool.h>

__attribute__((__nonnull__(1, 2)))
void	threaded_async(t_async *self, t_task *task)
{
	xft_threadpool_submit(&self->as.threaded, task, task->alloc_task);
}

__attribute__((__nonnull__(1, 2)))
void	threaded_await(t_async *self, t_task *task)
{
	(void)self;
	xft_threadpool_wait_task(task);
}

__attribute__((__nonnull__(1)))
t_result	xft_threaded_async(t_async *self, t_allocator allocator,
	t_sysinfo sysinfo, t_thread_opts opts)
{
	self->vtable = (t_async_vtable){
		.async = threaded_async,
		.await = threaded_await,
	};
	return (xft_threadpool_init(allocator, sysinfo, opts, &self->as.threaded));
}

__attribute__((__nonnull__(2)))
void	xft_threaded_async_destroy(t_allocator allocator, t_async *self)
{
	xft_threadpool_destroy(allocator, &self->as.threaded);
}
