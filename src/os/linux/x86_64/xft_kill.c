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

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline t_result	xft_kill(t_i32a pid, t_xft_signal sig)
{
	int		ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_kill),
		"D"((long)pid),
		"S"((long)sig)
		: "rcx", "r11", "memory"
	);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

# endif

#endif
