/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_lockf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_i32a	xft_fcntl(t_u32a fd, t_u32a cmd,
		const t_flock *restrict const arg)
{
	t_i32a	ret;

	__asm__ volatile (
		"syscall"
		: "=a" (ret)
		: "0" (SYS_FCNTL),
		"D" (fd),
		"S" (cmd),
		"d" (arg)
		: "rcx", "r11", "memory"
	);
	return ((t_i32a)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

t_i32a	xft_lockf(int fd)
{
	t_flock		fl;

	fl = (t_flock)
	{
		.l_type = F_RDLCK,
		.l_whence = SEEK_SET,
		.l_start = 0,
		.l_len = 0,
	};
	return (xft_fcntl((t_u32a)fd, F_SETLKW, &fl));
}

t_i32a	xft_unlockf(int fd)
{
	t_flock		fl;

	fl = (t_flock)
	{
		.l_type = F_UNLCK,
		.l_whence = SEEK_SET,
		.l_start = 0,
		.l_len = 0,
	};
	return (xft_fcntl((t_u32a)fd, F_SETLK, &fl));
}

# endif

#endif
