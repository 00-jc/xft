/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_perf_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "linux.h"
#include "bmi.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline int	xft_perf_event_open(const t_perf_event_attr *restrict attr,
		int group_fd)
{
	int					ret;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");

	r10 = (long)group_fd;
	r8 = PERF_FLAG_FD_CLOEXEC;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_PERF_EVENT_OPEN),
		"D"(attr),
		"S"((long) 0),
		"d"((long) -1),
		"r"(r10), "r"(r8)
		: "rcx", "r11", "memory"
	);
	return ((int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

# endif

#endif
