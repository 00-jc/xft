/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tailor_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:07:34 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"

__attribute__((nonnull(1)))
int	ft_tailor_new(t_tailor *t, t_f64 warmup_sec, t_u64a min_samples)
{
	t_u64a		actualtime;

	if (!ft_perf_create_counters(t->counters))
		return (0);
	t->arena = ft_new_arena_alloc();
	if (!t->arena.current)
		return (ft_perf_destroy_counters(t->counters), 0);
	actualtime = (t_u64a)(ft_dtern(warmup_sec < .75, .75, warmup_sec) * 1e9);
	t->phase1_ns = actualtime / 5;
	t->phase2_ns = actualtime - t->phase1_ns;
	t->rand_buffers = ft_fatptr(nullptr, 0);
	t->min_samples = ft_tern(min_samples < 150, 150, min_samples);
	return (1);
}

__attribute__((nonnull(1)))
void	ft_tailor_destroy(t_tailor *t)
{
	ft_destroy_arena(&t->arena);
	ft_perf_destroy_counters(t->counters);
}
