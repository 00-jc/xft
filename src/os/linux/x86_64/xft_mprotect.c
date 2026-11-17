/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mprotect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 09:54:35 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/08 09:58:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_syscalls.h>
#include <xft/bmi.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1)))
t_xft_sysres	xft_mprotect(t_any addr, t_size size, int prot)
{
	int		ret;
	t_u64a	r;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_mprotect),
		"D"(addr),
		"S"(size),
		"d"(prot)
		: "rcx", "r11", "memory"
	);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
