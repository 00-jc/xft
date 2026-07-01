/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sched_setaffinity.c                             :+:      :+:    :+:   */
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

__attribute__((__nonnull__(3), __always_inline__))
inline int	ft_sched_setaffinity(int pid, t_size cpusetsize,
		const t_u64a *restrict const mask)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_SCHED_SETAFFINITY),
		"D"(pid),
		"S"(cpusetsize),
		"d"(mask)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#else

__attribute__((__nonnull__(3), __always_inline__))
inline int	ft_sched_setaffinity(int pid, t_size cpusetsize,
		const t_u64a *restrict const mask)
{
	return ((int)syscall(SYS_SCHED_SETAFFINITY, pid, cpusetsize, mask));
}

#endif
