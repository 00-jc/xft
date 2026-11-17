/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mkdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/31 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_xft_sysres	xft_mkdir(const char *restrict path, t_u32a mode)
{
	int		ret;
	t_u64a	r;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_mkdir),
		"D"(path),
		"S"((long)mode)
		: "rcx", "r11", "memory"
	);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
