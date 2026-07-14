/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __aarch64__

__attribute__((__always_inline__))
inline t_any	ft_mmap(t_size size, long prot, long flags_extra)
{
	long	args[6];

	args[0] = (long) NULL;
	args[1] = (long)size;
	args[2] = prot;
	args[3] = MAP_PRIVATE | MAP_ANONYMOUS | flags_extra;
	args[4] = -1;
	args[5] = 0;
	return ((t_any)ft_syscall6(SYS_MMAP, args));
}

__attribute__((nonnull(1), __always_inline__))
inline void	ft_munmap(t_any restrict const mem, t_size size)
{
	const register long x8	__asm__("x8") = SYS_MUNMAP;
	const register long x0	__asm__("x0") = (long)mem;
	const register long x1	__asm__("x1") = (long)size;

	__asm__ volatile (
		"svc #0"
		:
		: "r"(x8), "r"(x0), "r"(x1)
		: "memory", "cc"
	);
}

#endif
