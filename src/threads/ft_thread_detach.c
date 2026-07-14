/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_detach.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 01:47:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 02:04:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "atomics.h"
#include "syscalls.h"

__attribute__((__nonnull__(1)))
void	ft_thread_detach(t_thread *__restrict__ const thread)
{
	t_thread_completion_stage			prev;
	t_thread_completion *__restrict__	comp;
	t_i32a								tid;

	comp = thread->completion;
	prev = __atomic_exchange_n(&comp->completion, DETACHED,
			__ATOMIC_ACQ_REL);
	if (prev == COMPLETED)
	{
		tid = __atomic_load_n(&comp->child_tid, __ATOMIC_ACQUIRE);
		while (tid != 0)
		{
			ft_futex_wait((t_u32a *)&comp->child_tid, (t_u32a)tid);
			tid = __atomic_load_n(&comp->child_tid, __ATOMIC_ACQUIRE);
		}
		ft_munmap(comp->mapped.mem, comp->mapped.size);
	}
}
