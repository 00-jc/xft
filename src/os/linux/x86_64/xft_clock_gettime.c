/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_clock_gettime.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_xft_sysres	xft_clock_gettime(t_timespec *__restrict__ const ts)
{
	t_i64a	ret;
	t_u64a	r;

	__asm__ volatile (
		"syscall"
		:"=a"(ret)
		:"0"((long)xft_sys_clock_gettime), "D"(1), "S"(ts)
		:"rcx", "r11", "memory"
	);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
