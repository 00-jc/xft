/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_cpu_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:03:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 13:06:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/mem.h>
#include <xft/syscalls.h>

#if defined(__linux__)
# include <xft/xft_p_syscalls.h>
#elif defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif

#if defined(__linux__)

__attribute__((pure, __nonnull__(1), unused, __always_inline__, __used__))
static inline t_size	xft__cpu_count(t_size *__restrict__ const set)
{
	const t_size	size = 128 / sizeof(t_size);
	t_size			i;
	t_size			sum;

	i = 0;
	sum = 0;
	while (i < size)
		sum += xft_popcount_u64(set[i++]);
	return (sum);
}

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_result	xft_get_cpu_count(t_size *__restrict__ const count)
{
	t_size		set[128 / sizeof(t_size)];
	int			res;

	xft_bzero(set, sizeof(set));
	res = xft_sched_getaffinity(xft_getpid(), sizeof(set), set);
	if (__builtin_expect(res < 0, 0))
		return (KO);
	*count = xft__cpu_count(set);
	return (OK);
}

#elif defined(_WIN32)

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_result	xft_get_cpu_count(t_size *__restrict__ const count)
{
	DWORD_PTR	proc;
	DWORD_PTR	sys;

	if (__builtin_expect(!GetProcessAffinityMask(GetCurrentProcess(),
				&proc, &sys), 0))
		return (KO);
	*count = xft_popcount_u64(proc);
	return (OK);
}

#endif
