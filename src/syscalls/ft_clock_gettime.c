/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clock_gettime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 21:56:17 by username          #+#    #+#             */
/*   Updated: 2026/06/28 23:38:01 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__always_inline__, __nonnull__(1)))
inline t_i64a	ft_clock_gettime(t_timespec *__restrict__ const ts)
{
	t_i64a	ret;

	__asm__ (
		"syscall"
		:"=a"(ret)
		:"0"(SYS_CLOCK_GETTIME), "D"(1), "S"(ts)
		:"rcx", "r11", "memory"
		);
	return (ret);
}

#else

__attribute__((__always_inline__, __nonnull__(1)))
inline t_i64a	ft_clock_gettime(t_timespec *__restrict__ const ts)
{
	return ((t_i64a)syscall(SYS_CLOCK_GETTIME, 1, ts));
}

#endif
