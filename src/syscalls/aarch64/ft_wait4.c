/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/31 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "private/ft_p_syscalls.h"

#if defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

/*
 *	wait4 survives in the generic ABI (unlike wait/waitpid, which never
 *	existed there), so this is a straight 4-register call.
 */

__attribute__((__always_inline__))
inline t_i32	ft_wait4(t_i32 pid, t_i32a *status, t_i32 options,
		t_any rusage)
{
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	register long x3	__asm__("x3");

	x8 = SYS_WAIT4;
	x1 = (long)status;
	x2 = options;
	x3 = (long)rusage;
	x0 = pid;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2), "r"(x3)
		: "memory", "cc"
	);
	return ((t_i32)ft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

#endif
