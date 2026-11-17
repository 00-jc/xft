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

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_xft_sysres	xft_fork(t_i32 *restrict const pid)
{
	register long x0	__asm__("x0");
	t_u64a				r;

	x0 = XFT_SIGCHLD;
	__asm__ volatile (
		"mov x1, xzr\n\tmov x2, xzr\n\tmov x3, xzr\n\tmov x4, xzr\n\t"
		"mov x8, %[nr]\n\t"
		"svc #0"
		: "+r"(x0)
		: [nr] "i"(xft_sys_clone)
		: "memory", "cc", "x1", "x2", "x3", "x4", "x8"
	);
	*pid = (t_i32)xft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0);
	r = xft_tern(x0 < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(x0 == -xft_eintr || x0 == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
