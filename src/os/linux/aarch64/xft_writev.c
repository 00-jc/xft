/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_writev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2, 4), __always_inline__, __used__))
inline t_xft_sysres	xft_writev(int fd, t_iovec *restrict const buffers,
	t_size len, t_size *restrict const written)
{
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	t_u64a				r;

	x8 = xft_sys_writev;
	x1 = (long)buffers;
	x2 = (long)len;
	x0 = fd;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	*written = (t_size)xft_tern(x0 < 0, 0, (t_u64a)x0);
	r = xft_tern(x0 < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(x0 == -xft_eintr || x0 == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
