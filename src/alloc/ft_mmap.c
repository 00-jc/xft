/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

#ifdef __x86_64__

void	*ft_mmap(size_t size, long prot_extra, long flags_extra)
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
		: "0"(SYS_mmap),
		"D"((long) NULL),
		"S"((long) size),
		"d"((long) PROT_READ | PROT_WRITE | prot_extra),
		"r"(r8), "r"(r9), "r"(r10)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

__attribute__((nonnull(1)))
void	ft_munmap(void *restrict const mem, size_t size)
{
	__asm__ volatile (
		"syscall"
		:
		: "a"(SYS_munmap),
		"D"(mem),
		"S"(size)
		: "rcx", "r11", "memory"
	);
}

#else

void	*ft_mmap(size_t size, long prot_extra, long flags_extra)
{
	(void)prot_extra;
	(void)flags_extra;
	return (ft_alloc(size));
}

__attribute__((nonnull(1)))
void	ft_munmap(void *restrict const mem, size_t size)
{
	(void)size;
	ft_free((void **)&(void *){mem});
}

#endif
