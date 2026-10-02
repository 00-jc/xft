/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sigprocmask.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"
#include "xft_p_syscalls.h"
#include "types/signal_types.h"

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline int	xft_sigprocmask(t_u32a flags, t_sigset *__restrict__ const set,
	t_sigset *__restrict__ const oldest)
{
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	register long x3	__asm__("x3");

	x8 = SYS_RT_SIGPROCMASK;
	x1 = (long)set;
	x2 = (long)oldest;
	x3 = XFT_SIGSET_SIZE;
	x0 = flags;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2), "r"(x3)
		: "memory", "cc"
	);
	return ((int)xft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

# endif

#endif
