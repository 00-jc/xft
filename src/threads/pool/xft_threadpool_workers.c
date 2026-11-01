/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_threadpool_workers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 02:54:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 13:51:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_threadpool.h>
#include <stdatomic.h>

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline void	xft__stop_threads(t_allocator allocator, t_threadpool *tp,
	t_size it, t_tp_state mode)
{
	t_size		it2;

	if (allocator.vtable == nullptr || allocator.vtable->free == nullptr)
		__builtin_unreachable();
	atomic_store_explicit(&tp->shut_down, mode, xft_release);
	xft_send_signal_for_all(&tp->wake_up);
	it2 = 0;
	while (it2 < it)
		xft_thread_join(&tp->worker_handles[it2++]);
	allocator.vtable->free(allocator.allocator,
		xft_fatptr((t_any)tp->worker_handles, tp->handle_alloc_size));
	tp->worker_handles = nullptr;
}

__attribute__((__nonnull__(2), __always_inline__))
static inline t_result	xft__alloc_handles(t_allocator allocator,
	t_threadpool *tp)
{
	t_buffer		buffer;

	if (allocator.allocator == nullptr || allocator.vtable == nullptr
		|| allocator.vtable->allocate == nullptr)
		__builtin_unreachable();
	buffer = allocator.vtable->allocate(allocator.allocator,
			tp->n_workers * sizeof(t_thread), _Alignof(t_thread));
	if (__builtin_expect(buffer.mem == nullptr, 0))
		return (KO);
	tp->handle_alloc_size = buffer.size;
	tp->worker_handles = (t_any)buffer.mem;
	return (OK);
}

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_result	xft__init_threads(t_allocator allocator, t_sysinfo sysinfo,
	t_threadpool *tp)
{
	t_size				it;
	const t_size		upper_bound = tp->n_workers;
	t_thread_opts		opts;
	t_threadpool_arg	arg;

	if (__builtin_expect(xft__alloc_handles(allocator, tp) == KO, 0))
		return (KO);
	opts.fn = xft__thread_routine;
	opts.stack_size = XFT_THREAD_STACKSIZE;
	opts.argument = &arg;
	it = 0;
	while (it < upper_bound)
	{
		arg = (t_threadpool_arg){.tp = tp, .idx = (t_u32a)it, .claimed = 0};
		if (__builtin_expect(xft_thread_spawn(&tp->worker_handles[it],
					sysinfo, opts) == KO, 0))
			return ((void)(xft__stop_threads(allocator, tp, it,
					xft_tp_cancel)), KO);
		xft_wait_for_signal(&arg.claimed, 0);
		it++;
	}
	return (OK);
}
