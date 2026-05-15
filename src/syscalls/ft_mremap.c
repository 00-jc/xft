/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mremap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:05:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 18:13:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "syscalls.h"

#ifdef __x86_64__

__attribute__((__nonnull__(3), __always_inline__))
inline void	*ft_mremap(size_t size, size_t new_size,
	void *addr, long flags_extra)
{
	void				*ret;
	register long r10	__asm__("r10");

	r10 = MREMAP_MAYMOVE | flags_extra;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_mremap),
		"D"(addr),
		"S"((long)size),
		"d"((long)new_size),
		"r"(r10)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#else

__attribute__((__nonnull__(3), __always_inline__))
inline void	*ft_mremap(size_t size, size_t new_size,
	void *addr, long flags_extra)
{
	return ((void *)syscall(SYS_mremap, addr, size,
			new_size, MREMAP_MAYMOVE | flags_extra));
}

#endif
