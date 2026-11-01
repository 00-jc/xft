/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_pool_cancel.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 14:11:02 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 14:11:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

static t_result	cancel_leaf(t_any arg)
{
	t_pool_test *__restrict__ const	s = arg;

	pool_spin();
	atomic_fetch_add_explicit(&s->count, 1, xft_relaxed);
	return (OK);
}

static t_result	cancel_owned(t_any arg)
{
	(void)arg;
	return (OK);
}

static void	cancel_submit_owned(t_pool_test *__restrict__ const s)
{
	t_buffer		b;
	t_thread_task	*t;
	t_u32a			it;

	it = 0;
	while (it++ < POOL_TEST_OWNED)
	{
		b = s->alloc.vtable->allocate(s->alloc.allocator,
				sizeof(t_thread_task), _Alignof(t_thread_task));
		pool_assert(b.mem != nullptr, "pool: owned alloc");
		t = (t_thread_task *)b.mem;
		pool_task_set(t, cancel_owned, nullptr, s->alloc);
		t->arg_model = xft_must_free_task_on_completion;
		xft_threadpool_submit(&s->tp, t, b.size);
	}
}

static void	cancel_check(t_pool_test *__restrict__ const s)
{
	t_u32a	it;
	t_u32a	ran;

	it = 0;
	ran = 0;
	while (it < POOL_TEST_TASKS)
	{
		pool_assert(s->inner[it].completion != 0, "pool: cancel completion");
		ran += s->inner[it++].result == OK;
	}
	pool_assert(ran == s->count, "pool: cancel ran");
	pool_assert(s->tp.global_q_head == nullptr && s->tp.q_len == 0,
		"pool: cancel global queue");
}

void	pool_round_cancel(t_pool_test *__restrict__ const s, t_sysinfo sysinfo)
{
	t_u32a	it;

	pool_assert(xft_threadpool_init(s->alloc, sysinfo, &s->tp) == OK,
		"pool: init");
	s->count = 0;
	it = 0;
	while (it < POOL_TEST_TASKS)
	{
		pool_task_set(&s->inner[it], cancel_leaf, s, s->alloc);
		xft_threadpool_submit(&s->tp, &s->inner[it], sizeof(s->inner[it]));
		it++;
	}
	cancel_submit_owned(s);
	xft_threadpool_cancel(s->alloc, &s->tp);
	cancel_check(s);
}
