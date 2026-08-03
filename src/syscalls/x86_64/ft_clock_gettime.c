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
#include "bmi.h"
#include "private/ft_p_syscalls.h"

#if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__always_inline__, __nonnull__(1)))
inline t_i64a	ft_clock_gettime(t_timespec *__restrict__ const ts)
{
	t_i64a	ret;

	__asm__ volatile (
		"syscall"
		:"=a"(ret)
		:"0"(SYS_CLOCK_GETTIME), "D"(1), "S"(ts)
		:"rcx", "r11", "memory"
		);
	return ((t_i64a)ft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

#endif
