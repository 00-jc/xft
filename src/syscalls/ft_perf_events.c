/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perf_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_perf_event_open(const struct perf_event_attr *restrict attr,
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
	return (ret);
}

#else

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_perf_event_open(const struct perf_event_attr *restrict attr,
		int group_fd)
{
	return ((int)syscall(SYS_PERF_EVENT_OPEN, attr, 0, -1, group_fd,
			PERF_FLAG_FD_CLOEXEC));
}

#endif
