/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_units.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_tailor.h>
#include <xft/indexmap.h>
#include <xft/mem.h>
#include <xft/cstr.h>

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline t_result	xft__units_alloc(t_tailor *t, t_tailor_units *u,
	t_size size)
{
	u->units = xft_arena_alloc(&t->arena, sizeof(t_tailor_unit) * size, 64);
	u->tasks = xft_arena_alloc(&t->arena, sizeof(t_thread_task) * size, 64);
	u->order = xft_arena_alloc(&t->arena, sizeof(t_tailor_job *) * size, 64);
	u->uid = xft_arena_alloc(&t->arena, sizeof(t_size) * size, 64);
	if (__builtin_expect(u->units == nullptr || u->tasks == nullptr
			|| u->order == nullptr || u->uid == nullptr, 0))
		return (KO);
	xft_memset(u->units, 0, sizeof(t_tailor_unit) * size);
	u->n = 0;
	u->map = xft_new_indexmap_with(xft_arena_allocator(&t->arena), size);
	return ((t_result)(u->map.soa.ptr != nullptr));
}

__attribute__((__nonnull__(1, 2, 3), __always_inline__))
static inline t_result	xft__units_assign(t_tailor *t, t_tailor_units *u,
	const t_tailor_job *jobs, t_size size)
{
	t_buffer	key;
	t_size		i;

	i = 0;
	while (i < size)
	{
		u->uid[i] = u->n;
		if (jobs[i].result.group != nullptr)
		{
			key = xft_fatptr((const t_u8 *)jobs[i].result.group,
					xft_strlen(jobs[i].result.group));
			u->uid[i] = xft_indexmap_lookup(&u->map, key);
			if (u->uid[i] == INDEXMAP_NPOS && !xft_indexmap_insert(
					xft_arena_allocator(&t->arena), &u->map, key, u->n))
				return (KO);
		}
		if (u->uid[i] == INDEXMAP_NPOS || u->uid[i] == u->n)
			u->uid[i] = u->n++;
		u->units[u->uid[i]].n++;
		u->units[u->uid[i]].exclusive |= jobs[i].exclusive;
		++i;
	}
	return (OK);
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline void	xft__units_fill(t_tailor_units *u, t_tailor_job *jobs,
	t_size size)
{
	t_size	k;
	t_size	off;

	k = 0;
	off = 0;
	while (k < u->n)
	{
		u->units[k].jobs = u->order + off;
		off += u->units[k].n;
		u->units[k++].n = 0;
	}
	k = 0;
	while (k < size)
	{
		u->units[u->uid[k]].jobs[u->units[u->uid[k]].n++] = jobs + k;
		++k;
	}
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline void	xft__units_tasks(t_tailor *t, t_tailor_units *u)
{
	t_size	pass;
	t_size	k;
	t_size	m;

	m = 0;
	pass = 0;
	while (pass < 2)
	{
		k = 0;
		while (k < u->n)
		{
			if (u->units[k].exclusive == (pass == 1))
				u->tasks[m++] = (t_thread_task){.f = xft_tailor_unit,
					.arg = &u->units[k], .arg_size = sizeof(t_tailor_unit),
					.allocator = xft_arena_allocator(&t->arena),
					.arg_model = xft_must_keep_all_alive};
			++k;
		}
		if (pass++ == 0)
			u->n_parallel = m;
	}
}

__attribute__((__nonnull__(1, 2)))
t_result	xft_tailor_units(t_tailor *t, t_tailor_units *u, t_size size)
{
	t_tailor_job *const	jobs = (t_tailor_job *)t->jobs.buf.mem;

	if (__builtin_expect(!xft__units_alloc(t, u, size)
			|| !xft__units_assign(t, u, jobs, size), 0))
		return (KO);
	xft__units_fill(u, jobs, size);
	xft__units_tasks(t, u);
	return (OK);
}
