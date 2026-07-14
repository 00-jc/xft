/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 01:47:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 01:47:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "atomics.h"
#include "syscalls.h"

__attribute__((__nonnull__(1)))
t_result	ft_thread_join(t_thread *__restrict__ const thread)
{
	t_thread_completion *__restrict__	comp;
	t_i32								tid;

	comp = thread->completion;
	tid = __atomic_load_n(&comp->child_tid, __ATOMIC_ACQUIRE);
	while (tid != 0)
	{
		ft_futex_wait((t_u32a *)&comp->child_tid, (t_u32a)tid);
		tid = __atomic_load_n(&comp->child_tid, __ATOMIC_ACQUIRE);
	}
	ft_munmap(comp->mapped.mem, comp->mapped.size);
	return (OK);
}
