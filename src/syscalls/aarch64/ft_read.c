/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "private/ft_p_syscalls.h"

#if defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__nonnull__(2), __always_inline__))
inline t_ssize	ft_read(int fd, t_u8 *restrict const buffer, t_size len)
{
	register long x8	__asm__("x8") = SYS_READ;
	register long x0		__asm__("x0");
	register long x1	__asm__("x1") = (long)buffer;
	register long x2	__asm__("x2") = (long)len;

	x0 = fd;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	return ((t_ssize)ft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

#endif
