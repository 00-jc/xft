/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigprocmask.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_syscalls.h"
#include "types/signal_types.h"

#ifdef __aarch64__

__attribute__((__always_inline__))
inline int	ft_sigprocmask(t_u32a flags, t_sigset *__restrict__ const set,
	t_sigset *__restrict__ const oldest)
{
	const register long x8	__asm__("x8") = SYS_RT_SIGPROCMASK;
	register long x0		__asm__("x0");
	const register long x1	__asm__("x1") = (long)set;
	const register long x2	__asm__("x2") = (long)oldest;

	x0 = flags;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	return ((int)x0);
}

#endif
