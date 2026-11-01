/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test_pool_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 14:11:02 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 14:11:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/threads/thread_test.h"

void	pool_assert(bool ok, const char *msg)
{
	xft_pin_invariant_msg(ok, xft_fatptr((t_u8 *)msg, xft_strlen(msg)));
}

void	pool_spin(void)
{
	volatile t_u32	i;

	i = 0;
	while (i < POOL_TEST_SPIN)
		i++;
}

void	pool_task_set(t_thread_task *__restrict__ const t,
	t_result (*f)(t_any), t_any arg, t_allocator alloc)
{
	t->f = f;
	t->arg = arg;
	t->allocator = alloc;
	t->arg_size = 0;
	t->arg_model = xft_must_keep_all_alive;
	t->result = KO;
	t->completion = 0;
}

void	pool_check_tasks(t_thread_task *__restrict__ const t, t_u32a n,
	bool wait)
{
	t_u32a	it;

	it = 0;
	while (it < n)
	{
		if (wait)
			xft_wait_for_signal(&t[it].completion, 0);
		pool_assert(t[it].completion != 0, "pool: task completion");
		pool_assert(t[it++].result == OK, "pool: task result");
	}
}
