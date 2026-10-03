/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_perf_create_counters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_perf.h"

__attribute__((const, __always_inline__))
static inline t_perf_event_attr	xft__getattr(t_u32a type, long conf)
{
	t_perf_event_attr		attr;

	xft_memset(&attr, 0, sizeof(attr));
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
static inline t_result	xft__init_hw(t_perf_counters c)
{
	t_size					i;
	t_perf_event_attr		attr;

	i = SW_COUNTERS_N;
	while (i < HW_COUNTERS_N + SW_COUNTERS_N)
	{
		attr = xft__getattr(PERF_TYPE_HARDWARE,
				get_hw_counters()[i - SW_COUNTERS_N]);
		c[i] = xft_perf_event_open(&attr, (int)c[0]);
		if (__builtin_expect(c[i] == -1, 0))
		{
			while (i)
				xft_close((int)c[--i]);
			return (KO);
		}
		++i;
	}
	return (OK);
}

__attribute__((__nonnull__(1)))
static inline t_result	xft__init_sw(t_perf_counters c)
{
	t_size					i;
	t_perf_event_attr		attr;

	attr = xft__getattr(PERF_TYPE_SOFTWARE, get_sw_counters()[0]);
	c[0] = xft_perf_event_open(&attr, -1);
	if (c[0] == -1)
		return (KO);
	i = 1;
	while (i < SW_COUNTERS_N)
	{
		attr = xft__getattr(PERF_TYPE_SOFTWARE, get_sw_counters()[i]);
		c[i] = xft_perf_event_open(&attr, (int)c[0]);
		if (__builtin_expect(c[i] == -1, 0))
		{
			while (i)
				xft_close((int)c[--i]);
			return (KO);
		}
		++i;
	}
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	xft_perf_create_counters(t_perf_counters c)
{
	if (__builtin_expect(xft__init_sw(c) == KO
			|| xft__init_hw(c) == KO, 0))
		return (KO);
	return (OK);
}
