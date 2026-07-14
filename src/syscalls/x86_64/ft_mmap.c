/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 13:15:08 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__always_inline__))
inline t_any	ft_mmap(t_size size, long prot, long flags_extra)
{
	t_any					ret;
	const register long r10	__asm__("r10") = MAP_PRIVATE
		| MAP_ANONYMOUS | flags_extra;
	const register long r9	__asm__("r9") = 0;
	const register long r8	__asm__("r8") = -1;

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
	__asm__ volatile (
		"syscall"
		:
		: "a"(SYS_MUNMAP),
		"D"(mem),
		"S"(size)
		: "rcx", "r11", "memory"
	);
}

#endif
