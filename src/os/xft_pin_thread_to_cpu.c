/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_pin_thread_to_cpu.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/os.h>

#if defined(__linux__)
# include <xft/mem.h>
# include <xft/xft_p_syscalls.h>
#elif defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif

#if defined(__linux__)

__attribute__((__always_inline__, __used__))
inline t_result	xft_pin_thread_to_cpu(t_u32 cpu)
{
	t_u64a			mask[128 / sizeof(t_u64a)];
	t_result		res;

	if (__builtin_expect(cpu >= sizeof(mask) * 8, 0))
		return ((t_result){.ok = KO, .err = xft_err_inval});
	xft_memset(mask, 0, sizeof(mask));
	mask[cpu >> 6] |= (t_u64a)1 << (cpu & 63);
	res = (t_result){.err = xft_err_retry};
	while (xft_should_retry(res))
		res = xft_sched_setaffinity(0, sizeof(mask), mask);
	return (res);
}

#elif defined(_WIN32)

__attribute__((__always_inline__, __used__))
inline t_result	xft_pin_thread_to_cpu(t_u32 cpu)
{
	if (__builtin_expect(cpu >= sizeof(DWORD_PTR) * 8, 0))
		return ((t_result){.ok = KO, .err = xft_err_inval});
	if (__builtin_expect(SetThreadAffinityMask(GetCurrentThread(),
				(DWORD_PTR)1 << cpu) == 0, 0))
		return ((t_result){.ok = KO, .err = xft_err_none});
	return ((t_result){.ok = OK});
}

#endif
