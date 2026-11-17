/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sendfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 15:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(4), __always_inline__, __used__))
inline t_xft_sysres	xft_sendfile(int out_fd, int in_fd, t_i64a *restrict offset,
	t_size *restrict const count)
{
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	register long x3	__asm__("x3");
	t_u64a				r;

	x1 = in_fd;
	x2 = (long)offset;
	x3 = (long)*count;
	x0 = out_fd;
	__asm__ volatile (
		"mov x8, %[nr]\n\t"
		"svc #0"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), [nr] "i"(xft_sys_sendfile)
		: "memory", "cc", "x8"
	);
	*count = (t_size)xft_tern(x0 < 0, 0, (t_u64a)x0);
	r = xft_tern(x0 < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(x0 == -xft_eintr || x0 == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
