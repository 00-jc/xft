/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clock_gettime.c                                 :+:      :+:    :+:   */
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
