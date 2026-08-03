/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:26:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__always_inline__))
inline t_any	ft_mmap(t_size size, long prot, long flags_extra)
{
	t_any					ret;
	register long r10		__asm__("r10");
	register long r9		__asm__("r9");
	register long r8		__asm__("r8");

	r10 = MAP_PRIVATE | MAP_ANONYMOUS | flags_extra;
	r9 = 0;
	r8 = -1;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_MMAP),
		"D"((long) NULL),
		"S"((long) size),
		"d"(prot),
		"r"(r8), "r"(r9), "r"(r10)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

__attribute__((nonnull(1), __always_inline__))
inline void	ft_munmap(t_any restrict const mem, t_size size)
{
	t_i64a	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_MUNMAP),
		"D"(mem),
		"S"(size)
		: "rcx", "r11", "memory"
	);
	(void)ret;
}

#endif
