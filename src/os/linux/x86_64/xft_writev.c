/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_writev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:00:59 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2, 4), __always_inline__, __used__))
inline t_xft_sysres	xft_writev(int fd, t_iovec *restrict const buffers,
	t_size len, t_size *restrict const written)
{
	t_ssize	ret;
	t_u64a	r;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_writev),
		"D"(fd),
		"S"(buffers),
		"d"(len)
		: "rcx", "r11", "memory"
	);
	*written = (t_size)xft_tern(ret < 0, 0, (t_u64a)ret);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
