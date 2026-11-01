/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_pool_wait.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 14:52:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 14:52:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

#ifdef __linux__

static t_result	wait_leaf(t_any arg)
{
	t_pool_test *__restrict__ const	s = arg;

	pool_spin();
	atomic_fetch_add_explicit(&s->count, 1, xft_relaxed);
	return (OK);
}

static t_result	wait_outer(t_any arg)
{
	const t_pool_job *__restrict__ const	job = arg;
	t_pool_test *__restrict__ const			s = job->s;
	t_thread_task *__restrict__ const		kids = &s->inner[job->idx
		* s->n_inner];
	t_u32a									it;

	it = 0;
	while (it < s->n_inner)
	{
		pool_task_set(&kids[it], wait_leaf, s, s->alloc);
		xft_threadpool_submit(&s->tp, &kids[it], sizeof(kids[it]));
		it++;
	}
	it = 0;
	while (it < s->n_inner)
		xft_threadpool_wait_task(&kids[it++]);
	pool_check_tasks(kids, s->n_inner, false);
	atomic_fetch_add_explicit(&s->count, 1, xft_relaxed);
	return (OK);
}

static void	wait_check(t_pool_test *__restrict__ const s)
{
	t_u32a	it;

	it = 0;
	while (it < s->n_outer)
		xft_threadpool_wait_task(&s->outer[it++]);
	pool_check_tasks(s->outer, s->n_outer, false);
	pool_check_tasks(s->inner, s->n_outer * s->n_inner, false);
	pool_assert(s->count == s->n_outer + s->n_outer * s->n_inner,
		"pool: wait count");
}

void	pool_round_wait(t_pool_test *__restrict__ const s, t_sysinfo sysinfo)
{
	t_u32a	it;

	pool_assert(xft_threadpool_init(s->alloc, sysinfo, &s->tp) == OK,
		"pool: init");
	s->count = 0;
	s->n_outer = POOL_TEST_OUTER;
	s->n_inner = POOL_TEST_INNER;
	it = 0;
	while (it < s->n_outer)
	{
		s->jobs[it] = (t_pool_job){.s = s, .idx = it};
		pool_task_set(&s->outer[it], wait_outer, &s->jobs[it], s->alloc);
		xft_threadpool_submit(&s->tp, &s->outer[it], sizeof(s->outer[it]));
		it++;
	}
	wait_check(s);
	xft_threadpool_destroy(s->alloc, &s->tp);
}

#endif
