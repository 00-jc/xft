/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_wait4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/31 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__always_inline__, __used__))
inline t_i32	xft_wait4(t_i32 pid, t_i32a *status, t_i32 options,
		t_any rusage)
{
	return ((t_i32)syscall(SYS_WAIT4, pid, status, options, rusage));
}

# endif

#endif
