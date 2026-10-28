/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_cpu_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:03:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/28 22:35:25 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/os.h>

#if defined(__linux__)
# include <xft/xft_p_syscalls.h>
#elif defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif

#if defined(__linux__)

__attribute__((pure, __nonnull__(1), unused, __always_inline__, __used__))
static inline t_size	xft__cpu_count(const t_u64a *__restrict__ const s,
	const t_size b)
{
	const t_size	n = b >> 3;

	return (xft_tern_s((b & 7) != 0,
			xft_popcount_u32(((const t_u32a *)s)[(b >> 2) - 1]), 0)
		+ xft_tern_s(n > 0, (t_size)xft_popcount_u64(s[0]), 0)
		+ xft_tern_s(n > 1, (t_size)xft_popcount_u64(s[1]), 0)
		+ xft_tern_s(n > 2, (t_size)xft_popcount_u64(s[2]), 0)
		+ xft_tern_s(n > 3, (t_size)xft_popcount_u64(s[3]), 0)
		+ xft_tern_s(n > 4, (t_size)xft_popcount_u64(s[4]), 0)
		+ xft_tern_s(n > 5, (t_size)xft_popcount_u64(s[5]), 0)
		+ xft_tern_s(n > 6, (t_size)xft_popcount_u64(s[6]), 0)
		+ xft_tern_s(n > 7, (t_size)xft_popcount_u64(s[7]), 0)
		+ xft_tern_s(n > 8, (t_size)xft_popcount_u64(s[8]), 0)
		+ xft_tern_s(n > 9, (t_size)xft_popcount_u64(s[9]), 0)
		+ xft_tern_s(n > 10, (t_size)xft_popcount_u64(s[10]), 0)
		+ xft_tern_s(n > 11, (t_size)xft_popcount_u64(s[11]), 0)
		+ xft_tern_s(n > 12, (t_size)xft_popcount_u64(s[12]), 0)
		+ xft_tern_s(n > 13, (t_size)xft_popcount_u64(s[13]), 0)
		+ xft_tern_s(n > 14, (t_size)xft_popcount_u64(s[14]), 0)
		+ xft_tern_s(n > 15, (t_size)xft_popcount_u64(s[15]), 0));
}

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_result	xft_get_cpu_count(t_size *__restrict__ const count)
{
	t_u64a		set[128 / sizeof(t_u64a)];
	int			res;

	res = xft_sched_getaffinity(xft_getpid(), sizeof(set), set);
	if (__builtin_expect(res < 0, 0))
		return (KO);
	*count = xft__cpu_count(set, (t_size)res);
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
	*count = xft_tern_s(proc == 0,
			GetActiveProcessorCount(ALL_PROCESSOR_GROUPS),
			(t_size)xft_popcount_u64(proc));
	return (OK);
}

#endif
