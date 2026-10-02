/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sched_getaffinity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 11:21:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 11:28:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "mem.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# pragma comment(lib, "kernel32.lib")
# include <stdbool.h>

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline int	xft_sched_getaffinity(t_i32a pid, t_size cpusetsize,
	const t_u64a *__restrict__ mask)
{
	HANDLE		h;
	DWORD_PTR	proc;
	DWORD_PTR	sys;
	bool		result;

	if (cpusetsize < sizeof(proc))
		__builtin_unreachable();
	h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, (DWORD)pid);
	if (__builtin_expect(!h, 0))
		return (-1);
	result = GetProcessAffinityMask(h, &proc, &sys);
	CloseHandle(h);
	if (__builtin_expect(!result, 0))
		return (-1);
	xft_bzero((t_any)mask, cpusetsize);
	*(t_u64a *)mask = proc;
	return (sizeof(proc));
}

#endif
