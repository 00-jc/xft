/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_kill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/20 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline t_result	xft_kill(t_i32a pid, t_xft_signal sig)
{
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");

	x8 = xft_sys_kill;
	x1 = (long)sig;
	x0 = (long)pid;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1)
		: "memory", "cc"
	);
	return ((t_result){.ok = x0 >= 0,
		.err = xft_tern(x0 < 0, (t_u64a)-x0, 0)});
}

# endif

#endif
