/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:29:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "private/ft_p_syscalls.h"

#if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

/*
 *	The 4th syscall argument goes in r10, not rcx: the kernel clobbers
 *	rcx with the return address, hence the pinned local.
 */

__attribute__((__always_inline__))
inline t_i32	ft_wait4(t_i32 pid, t_i32a *status, t_i32 options,
		t_any rusage)
{
	t_i32					ret;
	register long r10		__asm__("r10");

	r10 = (long)rusage;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_WAIT4),
		"D"((long)pid),
		"S"(status),
		"d"((long)options),
		"r"(r10)
		: "rcx", "r11", "memory"
	);
	return ((t_i32)ft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

#endif
