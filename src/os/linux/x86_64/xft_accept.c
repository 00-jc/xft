/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_accept.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 15:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(4), __always_inline__, __used__))
inline t_xft_sysres	xft_accept(int fd, int flags, t_sockaddr_in6 *restrict addr,
	int *restrict const conn)
{
	int					ret;
	register long r10	__asm__("r10");
	t_u64a				r;
	t_u32a				len;

	len = sizeof(t_sockaddr_in6);
	r10 = (long)flags;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_accept4),
		"D"(fd),
		"S"(addr),
		"d"((long)&len),
		"r"(r10)
		: "rcx", "r11", "memory"
	);
	*conn = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
