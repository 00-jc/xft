/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tailor_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 15:03:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "io.h"

__attribute__((__nonnull__(1)))
t_result	xft_new_tailor(t_tailor *t, t_f64 warmup_sec, t_u64a min_samples)
{
	t_u64a		actualtime;

	if (!xft_perf_create_counters(t->counters))
		return (KO);
	t->arena = xft_new_arena();
	if (!t->arena.current)
		return (xft_perf_destroy_counters(t->counters), KO);
	actualtime = (t_u64a)(xft_dtern(warmup_sec < .75, .75, warmup_sec) * 1e9);
	t->phase1_ns = actualtime / 5;
	t->phase2_ns = actualtime - t->phase1_ns;
	t->rand_buffers = xft_fatptr(nullptr, 0);
	t->min_samples = xft_tern(min_samples < 150, 150, min_samples);
	t->writer = xft_get_fs_writer(xft_fatptr(t->buffer, TAILOR_BUFFER_SIZE),
			xft_get_stdout());
	return (OK);
}

__attribute__((__nonnull__(1)))
void	xft_tailor_destroy(t_tailor *t)
{
	xft_destroy_arena(&t->arena);
	xft_perf_destroy_counters(t->counters);
}
