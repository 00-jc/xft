/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
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
#include "private/ft_p_syscalls.h"

#if defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

/*
 *	aarch64 has no bare "fork"/"vfork" syscall, only "clone". A plain
 *	fork is clone(SIGCHLD, 0, 0, 0, 0): no CLONE_VM/CLONE_THREAD, so the
 *	child gets a copy-on-write address space, and a NULL stack makes it
 *	resume on the parent's stack (which is COW'd as well).
 */

__attribute__((__always_inline__))
inline t_i32	ft_fork(void)
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
	x0 = FT_SIGCHLD;
	__asm__ volatile (
		"mov x8, %[nr]\n\t"
		"svc #0"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), "r"(x4), [nr] "i"(SYS_CLONE)
		: "memory", "cc", "x8"
	);
	return ((t_i32)ft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

#endif
