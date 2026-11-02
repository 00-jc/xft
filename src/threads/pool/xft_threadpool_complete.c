/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_complete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 14:02:25 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 14:02:25 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_threadpool.h>
#include <xft/atomics.h>
#include <stdatomic.h>
#include <stdint.h>

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft__handle_completion(t_threadpool *__restrict__ const tp,
	t_thread_task *__restrict__ const t)
{
	const t_thread_task_model	model = t->arg_model;

	if (t->allocator.vtable == nullptr || t->allocator.vtable->free == nullptr)
		__builtin_unreachable();
	if (model == xft_must_free_arg_on_completion
		|| model == xft_must_free_task_and_arg_on_completion)
		t->allocator.vtable->free(t->allocator.allocator,
			xft_fatptr(t->arg, t->arg_size));
	if (model == xft_must_free_task_on_completion
		|| model == xft_must_free_task_and_arg_on_completion)
		t->allocator.vtable->free(t->allocator.allocator,
			xft_fatptr((t_any)t, t->alloc_task));
	if (model == xft_must_free_arg_on_completion
		|| model == xft_must_keep_all_alive)
		xft_send_signal(&t->completion);
	if (atomic_fetch_sub_explicit(&tp->n_pending, 1, xft_release) == 1)
		xft_futex_wake(&tp->n_pending, INT32_MAX);
}
