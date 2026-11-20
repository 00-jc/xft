/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_signalfd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/20 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2, 4), __always_inline__, __used__))
inline t_result	xft_signalfd(int fd, const t_u64a *mask, int flags,
	int *restrict const sfd)
{
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	register long x3	__asm__("x3");

	x1 = (long)mask;
	x2 = XFT_SIGSET_SIZE;
	x3 = flags;
	x0 = fd;
	__asm__ volatile (
		"mov x8, %[nr]\n\t"
		"svc #0"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), [nr] "i"(xft_sys_signalfd4)
		: "memory", "cc", "x8"
	);
	*sfd = (int)xft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0);
	return ((t_result){.ok = x0 >= 0,
		.err = xft_tern(x0 < 0, (t_u64a)-x0, 0)});
}

# endif

#endif
