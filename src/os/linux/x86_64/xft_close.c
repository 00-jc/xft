/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline t_xft_sysres	xft_close(int fd)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_close),
		"D"(fd)
		: "rcx", "r11", "memory"
	);
	return ((t_xft_sysres)(ret >= 0 || ret == -xft_eintr));
}

# endif

#endif
