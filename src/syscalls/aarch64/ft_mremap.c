/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mremap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"
#include "syscalls.h"

#if defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__nonnull__(3), __always_inline__))
inline t_any	ft_mremap(t_size size, t_size new_size,
	t_any addr, long flags_extra)
{
	register long x8	__asm__("x8") = SYS_MREMAP;
	register long x0		__asm__("x0");
	register long x1	__asm__("x1") = (long)size;
	register long x2	__asm__("x2") = (long)new_size;
	register long x3	__asm__("x3") = MREMAP_MAYMOVE | flags_extra;

	x0 = (long)addr;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2), "r"(x3)
		: "memory", "cc"
	);
	return ((t_any)x0);
}

#endif
