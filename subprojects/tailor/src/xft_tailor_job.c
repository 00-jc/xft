/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_job.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_tailor.h>

__attribute__((__nonnull__(1), __always_inline__))
static inline t_result	xft__tailor_own_buffers(t_tailor_job *j)
{
	const t_buffer	*src = (const t_buffer *)j->buffers.mem;
	t_buffer		*dst;
	t_u8			*mem;
	t_size			i;

	if (j->buffers.size == 0)
		return (OK);
	dst = xft_arena_alloc(j->arena, j->buffers.size * sizeof(t_buffer), 64);
	if (__builtin_expect(dst == nullptr, 0))
		return (KO);
	i = 0;
	while (i < j->buffers.size)
	{
		mem = xft_arena_alloc(j->arena, src[i].size + 64, 64);
		if (__builtin_expect(mem == nullptr, 0))
			return (KO);
		mem += (t_uptr)src[i].mem & 63;
		xft_memcpy(mem, src[i].mem, src[i].size);
		dst[i] = xft_fatptr(mem, src[i].size);
		++i;
	}
	j->buffers.mem = (t_u8 *)dst;
	return (OK);
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_result	xft__tailor_unit_prepare(t_tailor_unit *u)
{
	t_size	m;

	m = 0;
	while (m < u->n)
	{
		u->jobs[m]->arena = &u->arena;
		u->jobs[m]->counters = u->counters;
		if (__builtin_expect(!xft__tailor_own_buffers(u->jobs[m])
				|| !xft_tailor_prepare(u->jobs[m]), 0))
			return (KO);
		++m;
	}
	return (OK);
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_result	xft__tailor_unit_rounds(t_tailor_unit *u)
{
	t_size	rounds;
	t_size	round;
	t_size	m;

	rounds = 0;
	m = 0;
	while (m < u->n)
	{
		rounds = xft_max_s(rounds, u->jobs[m]->plan.k_runs);
		++m;
	}
	round = 0;
	while (round++ < rounds)
	{
		m = 0;
		while (m < u->n)
		{
			if (__builtin_expect(!xft_tailor_sample(u->jobs[m++]), 0))
				return (KO);
		}
	}
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	xft_tailor_unit(t_any unit)
{
	t_tailor_unit *const	u = unit;
	t_arena_checkpoint		c;
	t_result				r;
	t_size					m;

	u->arena = xft_new_arena();
	if (__builtin_expect(u->arena.current == nullptr, 0))
		return (KO);
	if (__builtin_expect(!xft_perf_create_counters(u->counters), 0))
		return (xft_destroy_arena(&u->arena), KO);
	r = xft__tailor_unit_prepare(u);
	if (r == OK)
		r = xft__tailor_unit_rounds(u);
	m = 0;
	while (r == OK && m < u->n)
	{
		c = xft_arena_checkpoint(&u->arena);
		u->jobs[m]->status = xft_tailor_finish(u->jobs[m]);
		xft_arena_rewind(&u->arena, c);
		++m;
	}
	xft_perf_destroy_counters(u->counters);
	xft_destroy_arena(&u->arena);
	return (r);
}
