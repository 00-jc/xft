/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_wait4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:29:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __used__))
inline t_i32	xft_wait4(t_i32 pid, t_i32a *status, t_i32 options,
		t_any rusage)
{
	HANDLE	h;
	DWORD	wait;
	DWORD	code;

	(void)rusage;
	h = OpenProcess(SYNCHRONIZE | PROCESS_QUERY_LIMITED_INFORMATION,
			FALSE, pid);
	if (__builtin_expect(!h, 0))
		return (-1);
	wait = WaitForSingleObject(h,
			(DWORD)xft_tern(options & XFT_WNOHANG, 0, INFINITE));
	if (wait == WAIT_OBJECT_0 && status && GetExitCodeProcess(h, &code))
		*status = (t_i32a)((code & 0xff) << 8);
	CloseHandle(h);
	if (wait == WAIT_TIMEOUT)
		return (0);
	return ((t_i32)xft_tern(wait == WAIT_OBJECT_0, pid, (t_u64a)-1));
}

#endif
