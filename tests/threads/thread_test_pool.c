/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_pool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 14:11:02 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 14:11:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

static t_result	pool_leaf(t_any arg)
{
	t_pool_test *__restrict__ const	s = arg;

	if (xft__self()->tp != &s->tp)
		atomic_fetch_add_explicit(&s->bad_self, 1, xft_relaxed);
	pool_spin();
	atomic_fetch_add_explicit(&s->count, 1, xft_relaxed);
	return (OK);
}

static t_result	pool_outer(t_any arg)
{
	const t_pool_job *__restrict__ const	job = arg;
	t_pool_test *__restrict__ const			s = job->s;
	t_thread_task							*t;
	t_u32a									it;

	if (xft__self()->tp != &s->tp)
		atomic_fetch_add_explicit(&s->bad_self, 1, xft_relaxed);
	it = 0;
	while (it < s->n_inner)
	{
		t = &s->inner[job->idx * s->n_inner + it++];
		pool_task_set(t, pool_leaf, s, s->alloc);
		xft_threadpool_submit(&s->tp, t, sizeof(*t));
	}
	atomic_fetch_add_explicit(&s->count, 1, xft_relaxed);
	return (OK);
}

static void	pool_check(t_pool_test *__restrict__ const s, bool drain)
{
	pool_check_tasks(s->outer, s->n_outer, !drain);
	pool_check_tasks(s->inner, s->n_outer * s->n_inner, !drain);
	pool_assert(s->count == s->n_outer + s->n_outer * s->n_inner,
		"pool: task count");
	pool_assert(s->bad_self == 0, "pool: worker self");
	pool_assert(s->tp.global_q_head == nullptr && s->tp.q_len == 0,
		"pool: global queue");
}

static void	pool_round(t_pool_test *__restrict__ const s, t_sysinfo sysinfo,
	bool drain)
{
	t_u32a	it;

	pool_assert(xft_threadpool_init(s->alloc, sysinfo,
			xft_threadpool_default(), &s->tp) == OK,
		"pool: init");
	s->count = 0;
	s->bad_self = 0;
	it = 0;
	while (it < s->n_outer)
	{
		s->jobs[it] = (t_pool_job){.s = s, .idx = it};
		pool_task_set(&s->outer[it], pool_outer, &s->jobs[it], s->alloc);
		xft_threadpool_submit(&s->tp, &s->outer[it], sizeof(s->outer[it]));
		it++;
	}
	if (drain)
		xft_threadpool_destroy(s->alloc, &s->tp);
	pool_check(s, drain);
	if (!drain)
		xft_threadpool_destroy(s->alloc, &s->tp);
}

void	test_thread_pool(t_sysinfo sysinfo)
{
	static t_pool_test	s;
	t_u32a				round;

	s.alloc = xft_page_allocator();
	pool_assert(xft__self()->tp == nullptr, "pool: main self");
	round = 0;
	while (round++ < POOL_TEST_ROUNDS)
	{
		s.n_outer = POOL_TEST_OUTER;
		s.n_inner = POOL_TEST_INNER;
		pool_round(&s, sysinfo, false);
		pool_round(&s, sysinfo, true);
		s.n_outer = POOL_TEST_BIG_OUTER;
		s.n_inner = POOL_TEST_BIG_INNER;
		pool_round(&s, sysinfo, false);
		pool_round_cancel(&s, sysinfo);
		pool_round_wait(&s, sysinfo);
		pool_round_wait_all(&s, sysinfo);
		pool_round_wait_all_mp(&s, sysinfo);
		pool_round_fair(&s, sysinfo);
	}
}
