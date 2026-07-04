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

#if !defined(FT_REQUIRE_LIBC) && defined(__x86_64__)

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wait(t_u32a *__restrict__ const uaddr)
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
		"d"(FT_CONTESTED),
		"r"(r10),
		"r"(r8),
		"r"(r9)
		: "rcx", "r11", "memory"
		);
	return (ret);
}

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wake(t_u32a *__restrict__ const uaddr)
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
		"d"(FT_LOCKED),
		"r"(r10),
		"r"(r8),
		"r"(r9)
		: "rcx", "r11", "memory"
		);
	return (ret);
}

#else

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wait(t_u32a *__restrict__ const uaddr)
{
	return (syscall(SYS_FUTEX, uaddr, FUTEX_WAIT,
			FT_CONTESTED, NULL, NULL, 0));
}

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wake(t_u32a *__restrict__ const uaddr)
{
	return (syscall(SYS_FUTEX, uaddr, FUTEX_WAKE,
			FT_LOCKED, NULL, NULL, 0));
}

#endif
