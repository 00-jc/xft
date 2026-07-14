/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_clone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 02:10:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_syscalls.h"
#include "private/ft_p_thread.h"
#include "syscalls.h"
#include "threads.h"

__attribute__((__nonnull__(1), __always_inline__, unused))
inline t_result	ft__entry_exit(
	const t_thread_instance *__restrict__ const self)
{
	t_result	result;

	result = self->arg.fn(self->arg.arg);
	return (result);
}

__attribute__((const, __always_inline__, unused))
inline t_u64a	ft__get_flags(void)
{
	return (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND
		| CLONE_THREAD | CLONE_SYSVSEM | CLONE_SETTLS
		| CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID
		| CLONE_CHILD_SETTID);
}

__attribute__((__nonnull__(1, 4)))
t_result	ft__thread_clone(t_thread *__restrict__ const thread,
	t_thread_offset o, t_uptr tp, t_thread_instance *__restrict__ inst)
{
	t_user_desc					ud;
	t_clone_arg					carg;
	t_i32a						ret;
	t_result					result;
	t_thread_completion_stage	prev;

	carg = (t_clone_arg){.ctid = &inst->completion.child_tid,
		.ptid = &inst->completion.child_tid,
		.stack = inst->completion.mapped.mem + o.stack_offset,
		.tls = ft__settls_arg(tp, &ud), .flags = ft__get_flags()};
	ret = ft_clone(&carg);
	if (ret == 0)
	{
		result = ft__entry_exit(inst);
		prev = __atomic_exchange_n(&inst->completion.completion,
				COMPLETED, __ATOMIC_ACQ_REL);
		if (prev == DETACHED)
			ft_thread_free_exit(&inst->completion);
		ft_exit(result == KO);
	}
	if (__builtin_expect(ret < 0, 0))
		return ((void)ft_munmap(inst->completion.mapped.mem, o.total_map), KO);
	return ((void)(thread->handle = ret), OK);
}
