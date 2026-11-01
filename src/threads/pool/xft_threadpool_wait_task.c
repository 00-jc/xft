/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_wait_task.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 14:51:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 14:51:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_threadpool.h>
#include <xft/atomics.h>
#include <stdatomic.h>

__attribute__((__nonnull__(1), __flatten__))
void	xft_threadpool_wait_task(t_thread_task *__restrict__ const task)
{
	const t_tp_self *__restrict__ const	self = xft__self();

	while (self->tp != nullptr
		&& atomic_load_explicit(&task->completion, xft_acquire) == 0)
	{
		if (!xft__work_one(self->tp, self->idx))
			break ;
	}
	xft_wait_for_signal(&task->completion, 0);
}
