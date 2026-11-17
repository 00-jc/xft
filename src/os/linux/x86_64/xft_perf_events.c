/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_perf_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/types/linux_types.h>
#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1, 3), __always_inline__, __used__))
inline t_xft_sysres	xft_perf_event_open(const t_perf_event_attr *restrict attr,
	int group_fd, int *restrict const fd)
{
	int					ret;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");
	t_u64a				r;

	r10 = (long)group_fd;
	r8 = xft_perf_flag_fd_cloexec;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_perf_event_open),
		"D"(attr),
		"S"((long) 0),
		"d"((long) -1),
		"r"(r10), "r"(r8)
		: "rcx", "r11", "memory"
	);
	*fd = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
