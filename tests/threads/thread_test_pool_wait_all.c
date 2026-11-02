/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_pool_wait_all.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

static t_result	wait_all_leaf(t_any arg)
{
	t_pool_test *__restrict__ const	s = arg;

	atomic_fetch_add_explicit(&s->count, 1, xft_relaxed);
	return (OK);
}

static t_result	wait_all_outer(t_any arg)
{
	const t_pool_job *__restrict__ const	job = arg;
	t_pool_test *__restrict__ const			s = job->s;
	t_thread_task							*t;
	t_u32a									it;

	it = 0;
	while (it < s->n_inner)
	{
		t = &s->inner[job->idx * s->n_inner + it++];
		pool_task_set(t, wait_all_leaf, s, s->alloc);
		xft_threadpool_submit(&s->tp, t, sizeof(*t));
	}
	atomic_fetch_add_explicit(&s->count, 1, xft_relaxed);
	return (OK);
}

static void	wait_all_owned(t_pool_test *__restrict__ const s)
{
	t_buffer		b;
	t_thread_task	*t;
	t_u32a			it;

	it = 0;
	while (it++ < POOL_TEST_OWNED)
	{
		b = s->alloc.vtable->allocate(s->alloc.allocator,
				sizeof(t_thread_task), _Alignof(t_thread_task));
		pool_assert(b.mem != nullptr, "pool wait_all: owned alloc");
		t = (t_thread_task *)b.mem;
		pool_task_set(t, wait_all_leaf, s, s->alloc);
		t->arg_model = xft_must_free_task_on_completion;
		xft_threadpool_submit(&s->tp, t, b.size);
	}
}

static void	wait_all_batch(t_pool_test *__restrict__ const s)
{
	t_u32a	it;

	s->count = 0;
	it = 0;
	while (it < s->n_outer)
	{
		s->jobs[it] = (t_pool_job){.s = s, .idx = it};
		pool_task_set(&s->outer[it], wait_all_outer, &s->jobs[it], s->alloc);
		xft_threadpool_submit(&s->tp, &s->outer[it], sizeof(s->outer[it]));
		it++;
	}
	wait_all_owned(s);
	xft_threadpool_wait_all(&s->tp);
	pool_assert(s->count == s->n_outer + s->n_outer * s->n_inner
		+ POOL_TEST_OWNED, "pool wait_all: count");
	pool_check_tasks(s->outer, s->n_outer, false);
	pool_check_tasks(s->inner, s->n_outer * s->n_inner, false);
	pool_assert(s->tp.n_pending == 0, "pool wait_all: pending");
}

void	pool_round_wait_all(t_pool_test *__restrict__ const s,
	t_sysinfo sysinfo)
{
	t_u32a	it;

	pool_assert(xft_threadpool_init(s->alloc, sysinfo,
			xft_threadpool_default(), &s->tp) == OK,
		"pool wait_all: init");
	xft_threadpool_wait_all(&s->tp);
	s->n_outer = POOL_TEST_OUTER;
	s->n_inner = POOL_TEST_INNER;
	wait_all_batch(s);
	wait_all_batch(s);
	it = 0;
	while (it++ < POOL_TEST_TASKS)
	{
		pool_task_set(&s->outer[0], wait_all_leaf, s, s->alloc);
		xft_threadpool_submit(&s->tp, &s->outer[0], sizeof(s->outer[0]));
		xft_threadpool_wait_all(&s->tp);
		pool_assert(s->outer[0].completion != 0, "pool wait_all: ping");
	}
	xft_threadpool_destroy(s->alloc, &s->tp);
}
