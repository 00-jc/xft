/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sched_getaffinity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 11:21:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 11:28:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__nonnull__(3), __always_inline__))
inline int	ft_sched_getaffinity(t_i32a pid, t_size cpusetsize,
	const t_u64a *__restrict__ mask)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_SCHED_GETAFFINITY),
		"D"(pid),
		"S"(cpusetsize),
		"d"(mask)
		: "r11", "rcx", "memory"
	);
	return (ret);
}

#endif
