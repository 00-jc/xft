/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_futex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 21:04:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 13:14:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "types/atomic_types.h"

#ifdef __x86_64__

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wait(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	long					ret;
	const register long r8	__asm__("r8") = 0;
	const register long r9	__asm__("r9") = 0;
	const register long r10	__asm__("r10") = 0;

	__asm__ (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_FUTEX),
		"D"(uaddr),
		"S"(FUTEX_WAIT),
		"d"((long)val),
		"r"(r10),
		"r"(r8),
		"r"(r9)
		: "rcx", "r11", "memory"
		);
	return (ret);
}

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wake(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	long					ret;
	const register long r8	__asm__("r8") = 0;
	const register long r9	__asm__("r9") = 0;
	const register long r10	__asm__("r10") = 0;

	__asm__ (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_FUTEX),
		"D"(uaddr),
		"S"(FUTEX_WAKE),
		"d"((long)val),
		"r"(r10),
		"r"(r8),
		"r"(r9)
		: "rcx", "r11", "memory"
		);
	return (ret);
}

#endif
