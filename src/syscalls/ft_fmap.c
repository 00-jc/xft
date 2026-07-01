/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__always_inline__))
inline void	*ft_fmap(t_size size, int fd)
{
	void				*ret;
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
		"D"((long) NULL),
		"S"((long) size),
		"d"((long) PROT_READ),
		"r"(r10), "r"(r8), "r"(r9)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#else

__attribute__((__always_inline__))
inline void	*ft_fmap(t_size size, int fd)
{
	return ((void *)syscall(SYS_MMAP, NULL, size, PROT_READ,
			MAP_PRIVATE, fd, 0));
}

#endif
