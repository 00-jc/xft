/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_global.c                            :+:      :+:    :+:   */
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

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft__global_push(t_threadpool *__restrict__ const tp,
	t_thread_task *__restrict__ const task)
{
	task->next = nullptr;
	xft_mutex_lock(&tp->global_lock, xft_lock_fast);
	if (tp->global_q_tail == nullptr)
		tp->global_q_head = task;
	else
		tp->global_q_tail->next = task;
	tp->global_q_tail = task;
	atomic_fetch_add_explicit(&tp->q_len, 1, xft_relaxed);
	xft_mutex_unlock(&tp->global_lock);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_any	xft__global_pop(t_threadpool *__restrict__ const tp)
{
	t_thread_task	*task;

	if (atomic_load_explicit(&tp->q_len, xft_relaxed) == 0)
		return (nullptr);
	xft_mutex_lock(&tp->global_lock, xft_lock_fast);
	task = tp->global_q_head;
	if (task != nullptr)
	{
		tp->global_q_head = task->next;
		if (tp->global_q_head == nullptr)
			tp->global_q_tail = nullptr;
		atomic_fetch_sub_explicit(&tp->q_len, 1, xft_relaxed);
	}
	xft_mutex_unlock(&tp->global_lock);
	return (task);
}
