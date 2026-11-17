/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fstatx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_xft_sysres	xft_fstatx(int fd, t_u32a mask, t_statx *statxbuf)
{
	int					ret;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");
	t_u64a				r;

	r10 = mask;
	r8 = (long)statxbuf;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_statx),
		"D"((long)fd),
		"S"(""),
		"d"((long)xft_at_empty_path),
		"r"(r10), "r"(r8)
		: "rcx", "r11", "memory"
	);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
