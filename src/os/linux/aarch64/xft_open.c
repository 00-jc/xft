/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:36:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1, 4), __always_inline__, __used__))
inline t_result	xft_open(const char *restrict path, int flags, t_u32a mode,
	int *restrict const fd)
{
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	register long x3	__asm__("x3");

	x1 = (long)path;
	x2 = flags;
	x3 = (long)mode;
	x0 = xft_at_fdcwd;
	__asm__ volatile (
		"mov x8, %[nr]\n\t"
		"svc #0"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), [nr] "i"(xft_sys_openat)
		: "memory", "cc", "x8"
	);
	*fd = (int)xft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0);
	return ((t_result){.ok = x0 >= 0,
		.err = xft_tern(x0 < 0, (t_u64a)-x0, 0)});
}

# endif

#endif
