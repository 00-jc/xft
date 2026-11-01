/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_cancel.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 14:02:25 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 14:02:25 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_threadpool.h>
#include <xft/atomics.h>

__attribute__((__nonnull__(1)))
static inline void	xft__cancel_pending(t_threadpool *__restrict__ const tp)
{
	t_thread_task	*task;
	t_size			it;

	it = 0;
	while (it < tp->n_workers)
	{
		task = xft_ring_buffer_steal(&tp->worker_rings[it]);
		while (task != nullptr)
		{
			task->result = KO;
			xft__handle_completion(task);
			task = xft_ring_buffer_steal(&tp->worker_rings[it]);
		}
		it++;
	}
	task = xft__global_pop(tp);
	while (task != nullptr)
	{
		task->result = KO;
		xft__handle_completion(task);
		task = xft__global_pop(tp);
	}
}

__attribute__((__nonnull__(2), __flatten__))
void	xft_threadpool_cancel(t_allocator allocator,
	t_threadpool *__restrict__ const tp)
{
	xft__stop_threads(allocator, tp, tp->n_workers, xft_tp_cancel);
	xft__cancel_pending(tp);
	xft__free_rings(allocator, tp, tp->n_workers);
	tp->n_workers = 0;
}
