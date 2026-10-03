/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mkdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/31 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline int	xft_mkdir(const char *restrict path, t_u32a mode)
{
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");

	x8 = SYS_MKDIRAT;
	x1 = (long)path;
	x2 = (long)mode;
	x0 = AT_FDCWD;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	return ((int)xft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

# endif

#endif
