/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_nanos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_time.h"

#if defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__always_inline__))
inline t_u64a	ft_get_nanos(void)
{
	t_timespec	ts;

	ft_clock_gettime(&ts);
	return (((t_u64a)ts.tv_sec * 1000000000) + (t_u64a)ts.tv_nsec);
}

#elif !defined(__x86_64__)

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

/*
 *	the calibration window is ~10ms, so the ns delta stays far below
 *	2^32 and (delta << 32) fits in 64 bits: the division is a plain
 *	64/64 div, not a u128 one (which would libcall __udivti3).
 */

__attribute__((__always_inline__, __nonnull__(1)))
inline void	ft__clock_init(t_tsc *tsc)
{
	t_timespec	a;
	t_timespec	b;
	t_u64a		t0;
	t_u64a		t1;
	t_u64a		delta;

	ft_clock_gettime(&a);
	t0 = ft_rdtsc();
	ft_clock_gettime(&b);
	while (ft__ns_of(&b) - ft__ns_of(&a) < 10000000)
		ft_clock_gettime(&b);
	t1 = ft_rdtsc();
	delta = ft__ns_of(&b) - ft__ns_of(&a);
	tsc->mult = (t_i64a)((delta << 32) / (t1 - t0));
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
