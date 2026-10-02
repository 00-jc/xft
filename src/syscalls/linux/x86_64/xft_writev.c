/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_writev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 09:05:43 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 10:28:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_ssize	xft_writev(int fd, t_iovec *restrict const buffers, t_size len)
{
	t_ssize		ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_WRITEV),
		"D"(fd),
		"S"(buffers),
		"d"(len)
		: "rcx", "r11", "memory"
	);
	return ((t_ssize)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

# endif

#endif
