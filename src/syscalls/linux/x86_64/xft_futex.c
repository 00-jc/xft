/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_futex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 21:04:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:27:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "types/atomic_types.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i64a	xft_futex_wait(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	t_i64a					ret;
	register long r8		__asm__("r8");
	register long r9		__asm__("r9");
	register long r10		__asm__("r10");

	r8 = 0;
	r9 = 0;
	r10 = 0;
	__asm__ volatile (
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
	return ((t_i64a)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i64a	xft_futex_wake(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	t_i64a					ret;
	register long r8		__asm__("r8");
	register long r9		__asm__("r9");
	register long r10		__asm__("r10");

	r8 = 0;
	r9 = 0;
	r10 = 0;
	__asm__ volatile (
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
	return ((t_i64a)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

# endif

#endif
