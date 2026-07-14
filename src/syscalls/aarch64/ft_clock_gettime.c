/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clock_gettime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:36:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __aarch64__

__attribute__((__always_inline__, __nonnull__(1)))
inline t_i64a	ft_clock_gettime(t_timespec *__restrict__ const ts)
{
	const register long x8	__asm__("x8") = SYS_CLOCK_GETTIME;
	register long x0		__asm__("x0");
	const register long x1	__asm__("x1") = (long)ts;

	x0 = 1;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1)
		: "memory", "cc"
	);
	return (x0);
}

#endif
