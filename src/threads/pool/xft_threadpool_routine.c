/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_routine.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 02:54:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 13:50:59 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_threadpool.h>
#include <xft/atomics.h>
#include <stdatomic.h>

__attribute__((__nonnull__(1)))
static inline void	xft__drain_self(t_threadpool *__restrict__ const tp,
	t_u32a idx)
{
	t_ring_buffer *__restrict__ const	rb = &tp->worker_rings[idx];
	t_thread_task *__restrict__			task;

	task = xft_ring_buffer_steal(rb);
	while (task != nullptr)
	{
		task->result = task->f(task->arg);
		xft__handle_completion(task);
		if (atomic_load_explicit(&tp->shut_down, xft_relaxed) == xft_tp_cancel)
			return ;
		task = xft_ring_buffer_steal(rb);
	}
}

__attribute__((__nonnull__(1)))
static inline bool	xft__steal_other(t_threadpool *__restrict__ const tp,
	t_u32a idx)
{
	t_thread_task *__restrict__	task;
	t_size						it;

	it = xft_tern(idx + 1 >= tp->n_workers, 0, idx + 1);
	while (it != idx)
	{
		task = xft_ring_buffer_steal(&tp->worker_rings[it]);
		if (task != nullptr)
		{
			task->result = task->f(task->arg);
			xft__handle_completion(task);
			return (true);
		}
		it = xft_tern(it + 1 >= tp->n_workers, 0, it + 1);
	}
	return (false);
}

__attribute__((__nonnull__(1)))
static inline void	xft__work(t_threadpool *__restrict__ const tp,
	t_u32a idx)
{
	t_thread_task *__restrict__	task;

	xft__drain_self(tp, idx);
	while (true)
	{
		if (atomic_load_explicit(&tp->shut_down, xft_relaxed) == xft_tp_cancel)
			return ;
		task = xft__global_pop(tp);
		if (task != nullptr)
		{
			task->result = task->f(task->arg);
			xft__handle_completion(task);
		}
		else if (!xft__steal_other(tp, idx))
			return ;
		xft__drain_self(tp, idx);
	}
}

__attribute__((__nonnull__(1)))
bool	xft__work_one(t_threadpool *__restrict__ const tp, t_u32a idx)
{
	t_thread_task *__restrict__	task;

	task = xft_ring_buffer_steal(&tp->worker_rings[idx]);
	if (task == nullptr)
		task = xft__global_pop(tp);
	if (task == nullptr)
		return (xft__steal_other(tp, idx));
	task->result = task->f(task->arg);
	xft__handle_completion(task);
	return (true);
}

__attribute__((__nonnull__(1), __flatten__))
void	xft__thread_routine(t_any any)
{
	t_threadpool *__restrict__ const	tp = ((t_threadpool_arg *)any)->tp;
	const t_u32a						idx = ((t_threadpool_arg *)any)->idx;
	t_u32a								epoch;
	t_u32a								kill;

	(void)idx;
	xft_send_signal(&((t_threadpool_arg *)any)->claimed);
	xft__self()->tp = tp;
	xft__self()->idx = idx;
	epoch = xft_signal_epoch(&tp->wake_up);
	kill = xft_signal_epoch(&tp->shut_down);
	while (kill == xft_tp_running)
	{
		xft__work(tp, idx);
		atomic_fetch_add_explicit(&tp->n_maybe_parked, 1, xft_relaxed);
		xft_thread_fence(xft_seq_cst);
		xft_wait_for_signal(&tp->wake_up, epoch);
		atomic_fetch_sub_explicit(&tp->n_maybe_parked, 1, xft_relaxed);
		epoch = xft_signal_epoch(&tp->wake_up);
		kill = xft_signal_epoch(&tp->shut_down);
	}
	if (kill == xft_tp_drain)
		xft__work(tp, idx);
}
