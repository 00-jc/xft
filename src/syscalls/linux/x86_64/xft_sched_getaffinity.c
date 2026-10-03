/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sched_getaffinity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 11:21:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 11:28:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline int	xft_sched_getaffinity(t_i32a pid, t_size cpusetsize,
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
	return ((int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

# endif

#endif
