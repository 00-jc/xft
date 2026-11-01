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
	t_u64a	mask[128 / sizeof(t_u64a)];

	if (__builtin_expect(cpu >= sizeof(mask) * 8, 0))
		return (KO);
	xft_memset(mask, 0, sizeof(mask));
	mask[cpu >> 6] |= (t_u64a)1 << (cpu & 63);
	if (__builtin_expect(xft_sched_setaffinity(0, sizeof(mask), mask) == -1,
			0))
		return (KO);
	return (OK);
}

#elif defined(_WIN32)

__attribute__((__always_inline__, __used__))
inline t_result	xft_pin_thread_to_cpu(t_u32 cpu)
{
	if (__builtin_expect(cpu >= sizeof(DWORD_PTR) * 8, 0))
		return (KO);
	if (__builtin_expect(SetThreadAffinityMask(GetCurrentThread(),
				(DWORD_PTR)1 << cpu) == 0, 0))
		return (KO);
	return (OK);
}

#endif
