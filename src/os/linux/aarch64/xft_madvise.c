/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_madvise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_syscalls.h>
#include <xft/bmi.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1)))
t_xft_sysres	xft_madvise(t_any addr, t_size size, int advice)
{
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	t_u64a				r;

	x8 = xft_sys_madvise;
	x1 = (long)size;
	x2 = advice;
	x0 = (long)addr;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	r = xft_tern(x0 < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(x0 == -xft_eintr || x0 == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
