/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_io_uring_enter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/linux/uring.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_result	xft_io_uring_enter(int fd, t_io_uring_enter enter,
	int *restrict const submitted)
{
	int					ret;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");
	register long r9	__asm__("r9");

	r10 = (long)enter.flags;
	r8 = (long)enter.arg;
	r9 = (long)enter.argsz;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_io_uring_enter),
		"D"((long)fd),
		"S"((long)enter.to_submit),
		"d"((long)enter.min_complete),
		"r"(r10),
		"r"(r8),
		"r"(r9)
		: "rcx", "r11", "memory"
	);
	*submitted = (int)ret;
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

# endif

#endif
