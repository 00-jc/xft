/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_submit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 13:59:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 13:59:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_threadpool.h>
#include <xft/atomics.h>
#include <stdatomic.h>

__attribute__((__nonnull__(1)))
static inline void	xft__notify(t_threadpool *__restrict__ const tp)
{
	atomic_fetch_add_explicit(&tp->wake_up, 1, xft_release);
	xft_thread_fence(xft_seq_cst);
	if (atomic_load_explicit(&tp->n_maybe_parked, xft_relaxed) != 0)
		xft_futex_wake(&tp->wake_up, 1);
}

__attribute__((__nonnull__(1, 2), __flatten__))
void	xft_threadpool_submit(t_threadpool *__restrict__ const tp,
	t_thread_task *__restrict__ const task, t_size alloc_task)
{
	const t_tp_self *__restrict__ const	self = xft__self();

	task->alloc_task = alloc_task;
	task->completion = 0;
	if (self->tp != tp || xft_ring_buffer_submit_1ton(
			&tp->worker_rings[self->idx], task) == KO)
		xft__global_push(tp, task);
	xft__notify(tp);
}
