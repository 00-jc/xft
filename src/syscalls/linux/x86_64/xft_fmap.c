/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline t_any	xft_fmap(t_size size, int fd)
{
	t_any				ret;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");
	register long r9	__asm__("r9");

	r10 = MAP_PRIVATE;
	r8 = (long)fd;
	r9 = 0;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_MMAP),
		"D"((long)0),
		"S"((long) size),
		"d"((long) PROT_READ),
		"r"(r10), "r"(r8), "r"(r9)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

# endif

#endif
