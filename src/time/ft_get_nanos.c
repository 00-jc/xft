/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_nanos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:02:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 22:16:35 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_time.h"

#if !defined(__x86_64__)

__attribute__((__always_inline__))
inline t_u64a	ft_get_nanos(void)
{
	struct timespec		ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (((t_u64a)ts.tv_sec * 1000000000) + (t_u64a)ts.tv_nsec);
}

#else

__attribute__((__nonnull__(1), __always_inline__))
inline t_u64a	ft__ns_of(t_timespec *ts)
{
	return ((t_u64a)ts->tv_sec * 1000000000 + (t_u64a)ts->tv_nsec);
}

__attribute__((__always_inline__, __nonnull__(1)))
inline void	ft__clock_init(t_tsc *tsc)
{
	t_timespec	a;
	t_timespec	b;
	t_u64a		t0;
	t_u64a		t1;

	ft_clock_gettime(&a);
	t0 = ft_rdtsc();
	ft_clock_gettime(&b);
	while (ft__ns_of(&b) - ft__ns_of(&a) < 10000000)
		ft_clock_gettime(&b);
	t1 = ft_rdtsc();
	tsc->mult = (t_i64a)(((t_u128)(ft__ns_of(&b) - ft__ns_of(&a))
				<< 32) / (t1 - t0));
	tsc->base = (t_i64a)ft_rdtsc();
}

t_u64a	ft_get_nanos(void)
{
	static t_tsc	state_tsc;
	static bool		initialized = false;
	t_u64a			ticks;

	if (__builtin_expect(!initialized, 0))
	{
		ft__clock_init(&state_tsc);
		initialized = true;
	}
	ticks = ft_rdtsc() - state_tsc.base;
	return ((t_u64a)(((t_u128)ticks * state_tsc.mult) >> 32));
}

#endif
