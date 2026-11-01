/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_pool_fair.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

static t_result	fair_leaf(t_any arg)
{
	t_pool_test *__restrict__ const	s = arg;

	if (xft__self()->tp != &s->tp)
		atomic_fetch_add_explicit(&s->bad_self, 1, xft_relaxed);
	pool_spin();
	atomic_fetch_add_explicit(&s->count, 1, xft_relaxed);
	return (OK);
}

static void	fair_round(t_pool_test *__restrict__ const s, t_sysinfo sysinfo,
	bool drain)
{
	t_u32a	it;

	pool_assert(xft_threadpool_init(s->alloc, sysinfo,
			xft_threadpool_default(), &s->tp) == OK,
		"pool fair: init");
	s->count = 0;
	s->bad_self = 0;
	it = 0;
	while (it < POOL_TEST_TASKS)
		pool_task_set(&s->inner[it++], fair_leaf, s, s->alloc);
	xft_threadpool_submit_fair(&s->tp, s->inner, sizeof(s->inner[0]),
		POOL_TEST_TASKS);
	if (drain)
		xft_threadpool_destroy(s->alloc, &s->tp);
	it = 0;
	while (!drain && it < POOL_TEST_TASKS)
		xft_threadpool_wait_task(&s->inner[it++]);
	pool_check_tasks(s->inner, POOL_TEST_TASKS, false);
	pool_assert(s->count == POOL_TEST_TASKS, "pool fair: task count");
	pool_assert(s->bad_self == 0, "pool fair: worker self");
	pool_assert(s->tp.global_q_head == nullptr && s->tp.q_len == 0,
		"pool fair: global queue");
	if (!drain)
		xft_threadpool_destroy(s->alloc, &s->tp);
}

void	pool_round_fair(t_pool_test *__restrict__ const s, t_sysinfo sysinfo)
{
	fair_round(s, sysinfo, false);
	fair_round(s, sysinfo, true);
}
