/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_blocking_async.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_async.h>
#include <xft/mem.h>

__attribute__((__nonnull__(1, 2)))
void	blocking_async(t_async *self, t_task *task)
{
	const t_task_model	model = task->arg_model;
	const t_allocator	a = task->allocator;
	const t_buffer		arg = xft_fatptr(task->arg, task->arg_size);
	const t_buffer		task_buf = xft_fatptr((t_any)task, task->alloc_task);

	(void)self;
	if (a.vtable == nullptr || a.vtable->free == nullptr)
		__builtin_unreachable();
	task->result = task->f(task->arg);
	if (model == xft_must_free_arg_on_completion
		|| model == xft_must_free_task_and_arg_on_completion)
		a.vtable->free(a.allocator, arg);
	if (model == xft_must_free_task_on_completion
		|| model == xft_must_free_task_and_arg_on_completion)
		a.vtable->free(a.allocator, task_buf);
}

__attribute__((__nonnull__(1, 2)))
void	blocking_await(t_async *self, t_task *task)
{
	(void)self;
	(void)task;
}

t_async	xft_blocking_async(void)
{
	return ((t_async){
		.vtable = {
			.async = blocking_async,
			.await = blocking_await,
		},
	});
}
