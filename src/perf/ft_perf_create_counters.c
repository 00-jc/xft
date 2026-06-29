/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perf_create_counters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:49:27 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 22:59:39 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_perf.h"

/* manpage says cannot use inherit with groups,
 * well it's not anymore, its OK, see:
 * https://github.com/google/benchmark/blob/main/src/perf_counters.cc:201-204
 * */

__attribute__((const, __always_inline__))
static inline struct perf_event_attr	ft__getattr(t_u32a type, long conf)
{
	struct perf_event_attr	attr;

	ft_memset(&attr, 0, sizeof(attr));
	attr.read_format = PERF_FORMAT_TOTAL_TIME_ENABLED
		| PERF_FORMAT_TOTAL_TIME_RUNNING | PERF_FORMAT_GROUP;
	attr.type = type;
	attr.inherit = 1;
	attr.inherit_thread = 1;
	attr.config = conf;
	attr.exclude_user = 0;
	attr.exclude_kernel = 1;
	attr.exclude_callchain_kernel = 1;
	attr.disabled = 1;
	attr.exclude_hv = 1;
	return (attr);
}

__attribute__((__nonnull__(1)))
static inline t_result	ft__init_hw(t_perf_counters c)
{
	t_size					i;
	struct perf_event_attr	attr;

	i = SW_COUNTERS_N;
	while (i < HW_COUNTERS_N + SW_COUNTERS_N)
	{
		attr = ft__getattr(PERF_TYPE_HARDWARE,
				get_hw_counters()[i - SW_COUNTERS_N]);
		c[i] = ft_perf_event_open(&attr, (int)c[0]);
		if (__builtin_expect(c[i] == -1, 0))
		{
			while (i)
				ft_close((int)c[--i]);
			return (KO);
		}
		++i;
	}
	return (OK);
}

__attribute__((__nonnull__(1)))
static inline t_result	ft__init_sw(t_perf_counters c)
{
	t_size					i;
	struct perf_event_attr	attr;

	attr = ft__getattr(PERF_TYPE_SOFTWARE, get_sw_counters()[0]);
	c[0] = ft_perf_event_open(&attr, -1);
	if (c[0] == -1)
		return (KO);
	i = 1;
	while (i < SW_COUNTERS_N)
	{
		attr = ft__getattr(PERF_TYPE_SOFTWARE, get_sw_counters()[i]);
		c[i] = ft_perf_event_open(&attr, (int)c[0]);
		if (__builtin_expect(c[i] == -1, 0))
		{
			while (i)
				ft_close((int)c[--i]);
			return (KO);
		}
		++i;
	}
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	ft_perf_create_counters(t_perf_counters c)
{
	if (__builtin_expect(ft__init_sw(c) == KO
			|| ft__init_hw(c) == KO, 0))
		return (KO);
	return (OK);
}
