/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_nanos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_time.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __used__))
static inline t_u64a	xft__qpc_nanos(void)
{
	LARGE_INTEGER	c;
	LARGE_INTEGER	f;
	t_u64a			ticks;
	t_u64a			freq;

	QueryPerformanceCounter(&c);
	QueryPerformanceFrequency(&f);
	ticks = (t_u64a)c.QuadPart;
	freq = (t_u64a)f.QuadPart;
	return (ticks / freq * 1000000000 + ticks % freq * 1000000000 / freq);
}

# if !defined(__x86_64__)

__attribute__((__always_inline__, __used__))
inline t_u64a	xft_get_nanos(void)
{
	return (xft__qpc_nanos());
}

# else

__attribute__((__always_inline__, __nonnull__(1), __used__))
static inline void	xft__clock_init(t_tsc *tsc)
{
	t_u64a		a;
	t_u64a		b;
	t_u64a		t0;
	t_u64a		t1;

	a = xft__qpc_nanos();
	t0 = xft_rdtsc();
	b = xft__qpc_nanos();
	while (b - a < 10000000)
		b = xft__qpc_nanos();
	t1 = xft_rdtsc();
	tsc->mult = (t_i64a)(((b - a) << 32) / (t1 - t0));
	tsc->base = (t_i64a)xft_rdtsc();
}

t_u64a	xft_get_nanos(void)
{
	static t_tsc	state_tsc;
	static bool		initialized = false;
	t_u64a			ticks;

	if (__builtin_expect(!initialized, 0))
	{
		xft__clock_init(&state_tsc);
		initialized = true;
	}
	ticks = xft_rdtsc() - state_tsc.base;
	return ((t_u64a)(((t_u128)ticks * state_tsc.mult) >> 32));
}

# endif

#endif
