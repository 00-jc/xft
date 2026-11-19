/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_io_uring_register.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/linux/uring.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_result	xft_io_uring_register(int fd, t_io_uring_register reg,
	int *restrict const ret)
{
	int					res;
	register long r10	__asm__("r10");

	r10 = (long)reg.nr_args;
	__asm__ volatile (
		"syscall"
		: "=a"(res)
		: "0"((long)xft_sys_io_uring_register),
		"D"((long)fd),
		"S"((long)reg.opcode),
		"d"((long)reg.arg),
		"r"(r10)
		: "rcx", "r11", "memory"
	);
	*ret = (int)res;
	return ((t_result){.ok = res >= 0,
		.err = xft_tern(res < 0, (t_u64a)-res, 0)});
}

# endif

#endif
