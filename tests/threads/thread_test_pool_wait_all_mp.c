/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_pool_wait_all_mp.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

static t_result	mp_leaf(t_any arg)
{
	t_pool_test *__restrict__ const	s = arg;

	pool_spin();
	atomic_fetch_add_explicit(&s->count, 1, xft_relaxed);
	return (OK);
}

static void	mp_producer(t_any arg)
{
	const t_pool_job *__restrict__ const	job = arg;
	t_pool_test *__restrict__ const			s = job->s;
	t_thread_task *__restrict__ const		tasks = &s->inner[job->idx
		* s->n_inner];
	t_u32a									it;

	it = 0;
	while (it < s->n_inner)
	{
		pool_task_set(&tasks[it], mp_leaf, s, s->alloc);
		xft_threadpool_submit(&s->tp, &tasks[it], sizeof(tasks[it]));
		atomic_fetch_add_explicit(&s->submitted, 1, xft_release);
		it++;
	}
}

static void	mp_wait_loop(t_pool_test *__restrict__ const s, t_u32a total)
{
	t_u32a	snapshot;

	snapshot = 0;
	while (snapshot < total)
	{
		snapshot = atomic_load_explicit(&s->submitted, xft_acquire);
		xft_threadpool_wait_all(&s->tp);
		pool_assert(atomic_load_explicit(&s->count, xft_acquire) >= snapshot,
			"pool wait_all mp: task submitted before wait still pending");
	}
}

void	pool_round_wait_all_mp(t_pool_test *__restrict__ const s,
	t_sysinfo sysinfo)
{
	t_thread	threads[POOL_TEST_PRODUCERS];
	t_u32a		it;

	pool_assert(xft_threadpool_init(s->alloc, sysinfo,
			xft_threadpool_default(), &s->tp) == OK, "pool wait_all mp: init");
	s->count = 0;
	s->submitted = 0;
	s->n_outer = POOL_TEST_PRODUCERS;
	s->n_inner = POOL_TEST_TASKS / POOL_TEST_PRODUCERS;
	it = 0;
	while (it < s->n_outer)
	{
		s->jobs[it] = (t_pool_job){.s = s, .idx = it};
		pool_assert(xft_thread_spawn(&threads[it], sysinfo, (t_thread_opts){
				.fn = mp_producer, .argument = &s->jobs[it],
				.stack_size = XFT_THREAD_STACKSIZE}) == OK,
			"pool wait_all mp: spawn");
		it++;
	}
	mp_wait_loop(s, s->n_outer * s->n_inner);
	it = 0;
	while (it < s->n_outer)
		xft_thread_join(&threads[it++]);
	pool_assert(s->count == s->n_outer * s->n_inner, "pool wait_all mp: count");
	xft_threadpool_destroy(s->alloc, &s->tp);
}
