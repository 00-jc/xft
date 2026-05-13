/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perf_sampling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 21:34:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_perf.h"

__attribute__((__nonnull__(1, 2)))
void	ft_perf_start_sample(t_perf_counters c, t_perf_sample *t)
{
	ft_perf_counters_reset(c);
	t->ns = ft_get_nanos();
	ft_perf_counters_start(c);
}

__attribute__((__nonnull__(1, 2), __always_inline__))
static inline int	ft__get_sample_plexed(t_perf_counters c, t_u64 *v)
{
	size_t			i;
	t_perf_read		t;
	t_u8			adjust;
	t_f64			scale;

	i = 0;
	if (__builtin_expect(read((int)c[i],
				&t, sizeof(t)) != sizeof(t)
			|| t.running == 0, 0))
		return (0);
	adjust = t.running != t.enabled;
	if (adjust)
	{
		scale = (t_f64)t.enabled / (t_f64)t.running;
		while (i < t.nr)
		{
			v[i] = (t_u64)((t_f64)t.val[i] * scale);
			++i;
		}
	}
	else
		ft_memcpy(v, t.val, sizeof(t_u64) * (SW_COUNTERS_N + HW_COUNTERS_N));
	return (1);
}

__attribute__((__nonnull__(2, 3)))
int	ft_perf_collect_sample(size_t n,
	t_perf_counters c, t_perf_sample *s)
{
	t_u64a	v[SW_COUNTERS_N + HW_COUNTERS_N];
	t_u64a	t;

	ft_perf_counters_stop(c);
	t = ft_get_nanos();
	if (__builtin_expect(ft__get_sample_plexed(c, v) == 0, 0))
		return (0);
	s->n = n;
	s->ns = t - s->ns;
	s->alignment_faults = v[1];
	s->page_faults = v[2];
	s->cycles = v[3];
	s->instr = v[4];
	s->cache_ll = v[5];
	s->cache_miss = v[6];
	s->branches = v[7];
	s->branch_miss = v[8];
	return (1);
}
