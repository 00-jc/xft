/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_top.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_tailor.h>
#include <xft/atomics.h>
#include <xft/vec.h>

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline void	xft__tailor_dispatch(t_tailor *t, t_tailor_units *u)
{
	t_size	i;

	xft_threadpool_submit_fair(&t->pool, u->tasks, sizeof(*u->tasks),
		u->n_parallel);
	i = 0;
	while (i < u->n_parallel)
		xft_wait_for_signal(&u->tasks[i++].completion, 0);
	while (i < u->n)
	{
		xft_threadpool_submit_fair(&t->pool, u->tasks + i, sizeof(*u->tasks),
			1);
		xft_wait_for_signal(&u->tasks[i++].completion, 0);
	}
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_result	xft__tailor_collect(t_tailor *t, t_size size)
{
	const t_tailor_job *const	jobs = (const t_tailor_job *)t->jobs.buf.mem;
	t_size						i;
	t_result					r;

	r = OK;
	i = 0;
	while (i < size)
	{
		if (jobs[i].status == KO
			|| !xft_vec_push_back(xft_gpa_allocator(&t->gpa), &t->results,
				(const t_u8 *)&jobs[i].result, sizeof(t_tailor_result)))
			r = KO;
		++i;
	}
	xft_vec_clear(&t->jobs);
	return (r);
}

__attribute__((__nonnull__(1)))
t_result	xft_tailor_run(t_tailor *t)
{
	const t_size		size = xft_vec_len(&t->jobs, sizeof(t_tailor_job));
	t_arena_checkpoint	c;
	t_tailor_units		u;
	t_result			r;

	if (size == 0)
		return (OK);
	c = xft_arena_checkpoint(&t->arena);
	if (__builtin_expect(!xft_tailor_units(t, &u, size), 0))
		return (xft_arena_rewind(&t->arena, c), KO);
	xft__tailor_dispatch(t, &u);
	r = xft__tailor_collect(t, size);
	xft_arena_rewind(&t->arena, c);
	return (r);
}
