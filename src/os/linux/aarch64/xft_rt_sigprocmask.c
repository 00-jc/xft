/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_rt_sigprocmask.c                               :+:      :+:    :+:   */
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
inline t_result	xft_rt_sigprocmask(t_xft_sighow how, const t_u64a *set,
	t_u64a *oldset)
{
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	register long x3	__asm__("x3");

	x1 = (long)set;
	x2 = (long)oldset;
	x3 = XFT_SIGSET_SIZE;
	x0 = (long)how;
	__asm__ volatile (
		"mov x8, %[nr]\n\t"
		"svc #0"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), [nr] "i"(xft_sys_rt_sigprocmask)
		: "memory", "cc", "x8"
	);
	return ((t_result){.ok = x0 >= 0,
		.err = xft_tern(x0 < 0, (t_u64a)-x0, 0)});
}

# endif

#endif
