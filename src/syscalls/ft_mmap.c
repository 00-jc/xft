/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 14:14:24 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__always_inline__))
inline void	*ft_mmap(t_size size, long prot_extra, long flags_extra)
{
	void				*ret;
	register long r10	__asm__("r10");
	register long r9	__asm__("r9");
	register long r8	__asm__("r8");

	r10 = MAP_PRIVATE | MAP_ANONYMOUS | flags_extra;
	r9 = 0;
	r8 = -1;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_MMAP),
		"D"((long) NULL),
		"S"((long) size),
		"d"((long) PROT_READ | PROT_WRITE | prot_extra),
		"r"(r8), "r"(r9), "r"(r10)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

__attribute__((nonnull(1), __always_inline__))
inline void	ft_munmap(void *restrict const mem, t_size size)
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

#else

__attribute__((__always_inline__))
void	*ft_mmap(t_size size, long prot_extra, long flags_extra)
{
	return ((void *)syscall(SYS_MMAP,
			size,
			NULL,
			PROT_READ | PROT_WRITE | prot_extra,
			0,
			-1,
			MAP_ANONYMOUS | MAP_PRIVATE | flags_extra
		));
}

__attribute__((nonnull(1), __always_inline__))
inline void	ft_munmap(void *restrict const mem, t_size size)
{
	syscall(SYS_MUNMAP, mem, size);
}

#endif
