/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sched_getaffinity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 11:21:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 11:28:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(3, 4), __always_inline__, __used__))
inline t_xft_sysres	xft_sched_getaffinity(t_i32a pid, t_size cpusetsize,
	const t_u64a *__restrict__ mask,
	t_size *__restrict__ const written)
{
	int		ret;
	t_u64a	r;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_sched_getaffinity),
		"D"(pid),
		"S"(cpusetsize),
		"d"(mask)
		: "r11", "rcx", "memory"
	);
	*written = (t_size)xft_tern(ret < 0, 0, (t_u64a)ret);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
