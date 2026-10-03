/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/30 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "signals.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline t_i32	xft_fork(void)
{
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	register long x3	__asm__("x3");
	register long x4	__asm__("x4");

	x1 = 0;
	x2 = 0;
	x3 = 0;
	x4 = 0;
	x0 = XFT_SIGCHLD;
	__asm__ volatile (
		"mov x8, %[nr]\n\t"
		"svc #0"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), "r"(x4), [nr] "i"(SYS_CLONE)
		: "memory", "cc", "x8"
	);
	return ((t_i32)xft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

# endif

#endif
