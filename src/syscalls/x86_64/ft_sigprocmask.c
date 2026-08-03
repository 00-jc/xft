/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigprocmask.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:17:37 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:28:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"
#include "private/ft_p_syscalls.h"
#include "types/signal_types.h"

#if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__always_inline__))
inline int	ft_sigprocmask(t_u32a flags, t_sigset *__restrict__ const set,
	t_sigset *__restrict__ const oldest)
{
	int							ret;
	register long r10		__asm__("r10") = FT_SIGSET_SIZE;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_RT_SIGPROCMASK),
		"D"(flags),
		"S"(set),
		"d"(oldest),
		"r"(r10)
		: "r11", "rcx", "memory"
	);
	return ((int)ft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

#endif
