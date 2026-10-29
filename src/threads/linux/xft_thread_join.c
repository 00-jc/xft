/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_thread_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:43:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/threads.h>
#include <xft/xft_p_syscalls.h>

#if defined(__linux__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __flatten__))
void	xft_thread_join(t_thread *__restrict__ const thread)
{
	t_thread_instance *__restrict__ const	instance = thread->instance;
	t_u32a									tid;

	tid = __atomic_load_n(&instance->tid, __ATOMIC_ACQUIRE);
	while (tid != 0)
	{
		xft_futex_wait(&instance->tid, tid);
		tid = __atomic_load_n(&instance->tid, __ATOMIC_ACQUIRE);
	}
	xft_munmap(instance->base, instance->size);
}

__attribute__((__nonnull__(1)))
t_thread_id	xft_thread_id(const t_thread *__restrict__ const thread)
{
	return (__atomic_load_n(&thread->instance->tid, __ATOMIC_ACQUIRE));
}

#endif
