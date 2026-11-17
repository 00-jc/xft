/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_prlimit64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 23:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/28 23:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(4), __always_inline__, __used__))
inline t_xft_sysres	xft_prlimit64(t_i32a pid, t_xft_rlimit resource,
	const t_rlimit *new_limit, t_rlimit *__restrict__ old_limit)
{
	int					ret;
	register long r10	__asm__("r10");
	t_u64a				r;

	r10 = (long)old_limit;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_prlimit64),
		"D"((long)pid),
		"S"((long)resource),
		"d"(new_limit),
		"r"(r10)
		: "rcx", "r11", "memory"
	);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
