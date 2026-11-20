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

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline t_result	xft_rt_sigprocmask(t_xft_sighow how, const t_u64a *set,
	t_u64a *oldset)
{
	int					ret;
	register long r10	__asm__("r10");

	r10 = XFT_SIGSET_SIZE;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_rt_sigprocmask),
		"D"((long)how),
		"S"(set),
		"d"(oldset),
		"r"(r10)
		: "rcx", "r11", "memory"
	);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

# endif

#endif
