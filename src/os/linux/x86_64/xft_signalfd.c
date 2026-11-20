/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_signalfd.c                                     :+:      :+:    :+:   */
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

__attribute__((__nonnull__(2, 4), __always_inline__, __used__))
inline t_result	xft_signalfd(int fd, const t_u64a *mask, int flags,
	int *restrict const sfd)
{
	int					ret;
	register long r10	__asm__("r10");

	r10 = (long)flags;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_signalfd4),
		"D"((long)fd),
		"S"(mask),
		"d"((long)XFT_SIGSET_SIZE),
		"r"(r10)
		: "rcx", "r11", "memory"
	);
	*sfd = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

# endif

#endif
