/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_clock_gettime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_i64a	xft_clock_gettime(t_timespec *__restrict__ const ts)
{
	LARGE_INTEGER	freq;
	LARGE_INTEGER	count;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&count);
	ts->tv_sec = count.QuadPart / freq.QuadPart;
	ts->tv_nsec = (count.QuadPart % freq.QuadPart) * 1000000000LL
		/ freq.QuadPart;
	return (0);
}

#endif
