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
#include "bmi.h"
#include "private/ft_p_syscalls.h"

#if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

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
	return ((int)ft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

#endif
