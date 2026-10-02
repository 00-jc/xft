/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sched_setaffinity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# pragma comment(lib, "kernel32.lib")
# include <stdbool.h>

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline int	xft_sched_setaffinity(int pid, t_size cpusetsize,
		const t_u64a *restrict const mask)
{
	HANDLE	h;
	bool	result;

	if (cpusetsize < sizeof(DWORD_PTR))
		__builtin_unreachable();
	h = OpenProcess(PROCESS_SET_INFORMATION, FALSE, (DWORD)pid);
	if (__builtin_expect(!h, 0))
		return (-1);
	result = SetProcessAffinityMask(h, (DWORD_PTR)mask[0]);
	CloseHandle(h);
	return ((int)xft_tern(result, 0, (t_u64a)-1));
}

#endif
