/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sched_setaffinity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __aarch64__

__attribute__((__nonnull__(3), __always_inline__))
inline int	ft_sched_setaffinity(int pid, t_size cpusetsize,
		const t_u64a *restrict const mask)
{
	const register long x8	__asm__("x8") = SYS_SCHED_SETAFFINITY;
	register long x0		__asm__("x0");
	const register long x1	__asm__("x1") = (long)cpusetsize;
	const register long x2	__asm__("x2") = (long)mask;

	x0 = pid;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	return ((int)x0);
}

#endif
