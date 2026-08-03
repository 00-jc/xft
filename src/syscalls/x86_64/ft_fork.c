/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/30 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "private/ft_p_syscalls.h"

#if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__always_inline__))
inline t_i32	ft_fork(void)
{
	t_i32	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_FORK)
		: "rcx", "r11", "memory"
	);
	return ((t_i32)ft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

#endif
