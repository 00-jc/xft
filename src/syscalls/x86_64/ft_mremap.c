/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mremap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"
#include "syscalls.h"

#ifdef __x86_64__

__attribute__((__nonnull__(3), __always_inline__))
inline t_any	ft_mremap(t_size size, t_size new_size,
	t_any addr, long flags_extra)
{
	t_any				ret;
	register long r10	__asm__("r10");

	r10 = MREMAP_MAYMOVE | flags_extra;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_MREMAP),
		"D"(addr),
		"S"((long)size),
		"d"((long)new_size),
		"r"(r10)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#endif
