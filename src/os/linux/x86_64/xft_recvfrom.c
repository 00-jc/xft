/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_recvfrom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 17:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_xft_sysres	xft_recvfrom(int fd, t_iovec *restrict buf,
	t_xft_msg_opts opts, t_sockaddr_in6 *restrict from)
{
	t_ssize				ret;
	register long r8	__asm__("r8");
	register long r9	__asm__("r9");
	t_u64a				r;
	t_u32a				len;

	len = sizeof(t_sockaddr_in6);
	r8 = (long)from;
	r9 = (long)&len;
	__asm__ volatile (
		"mov %[fl], %%r10\n\t"
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_recvfrom),
		"D"(fd),
		"S"((long)buf->mem),
		"d"((long)buf->size),
		"r"(r8), "r"(r9), [fl] "r"((long)opts.flags)
		: "rcx", "r10", "r11", "memory"
	);
	buf->size = (t_size)xft_tern(ret < 0, 0, (t_u64a)ret);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
