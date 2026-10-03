/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline t_any	xft_mmap(t_size size, t_u64a prot, t_u64a flags_extra)
{
	t_u64a	args[6];

	args[0] = 0;
	args[1] = (t_u64a)size;
	args[2] = prot;
	args[3] = MAP_PRIVATE | MAP_ANONYMOUS | flags_extra;
	args[4] = -1;
	args[5] = 0;
	return ((t_any)xft_syscall6(SYS_MMAP, args));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_munmap(t_any restrict const mem, t_size size)
{
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");

	x8 = SYS_MUNMAP;
	x0 = (long)mem;
	x1 = (long)size;
	__asm__ volatile (
		"svc #0"
		:
		: "r"(x8), "r"(x0), "r"(x1)
		: "memory", "cc"
	);
}

# endif

#endif
