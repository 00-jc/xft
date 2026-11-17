/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sendto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 17:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_xft_sysres	xft_sendto(int fd, t_iovec *restrict buf,
	t_xft_msg_opts opts, const t_sockaddr_in6 *restrict dest)
{
	t_ssize				ret;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");
	register long r9	__asm__("r9");
	t_u64a				r;

	r10 = opts.flags | xft_msg_nosignal;
	r8 = (long)dest;
	r9 = (long)xft_tern(dest && dest->sin6_family == xft_af_inet6,
			sizeof(t_sockaddr_in6), sizeof(t_sockaddr_in));
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_sendto),
		"D"(fd),
		"S"((long)buf->mem),
		"d"((long)buf->size),
		"r"(r10), "r"(r8), "r"(r9)
		: "rcx", "r11", "memory"
	);
	buf->size = (t_size)xft_tern(ret < 0, 0, (t_u64a)ret);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
