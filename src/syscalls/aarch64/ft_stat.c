/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat.c                                          :+:      :+:    :+:   */
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

/*
 *	aarch64 has no bare "stat" syscall, only "newfstatat".
 */

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_stat(const char *restrict path, t_stat *statbuf)
{
	register long x8	__asm__("x8") = SYS_NEWFSTATAT;
	register long x0		__asm__("x0");
	register long x1	__asm__("x1") = (long)path;
	register long x2	__asm__("x2") = (long)statbuf;
	register long x3	__asm__("x3") = 0;

	x0 = AT_FDCWD;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2), "r"(x3)
		: "memory", "cc"
	);
	return ((int)ft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

#endif
