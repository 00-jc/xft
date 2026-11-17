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

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_xft_sysres	xft_fcntl(t_u32a fd, t_u32a cmd,
		const t_flock *restrict const arg)
{
	t_i32a	ret;
	t_u64a	r;

	__asm__ volatile (
		"syscall"
		: "=a" (ret)
		: "0"((long)xft_sys_fcntl),
		"D" (fd),
		"S" (cmd),
		"d" (arg)
		: "rcx", "r11", "memory"
	);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

t_xft_sysres	xft_lockf(int fd)
{
	t_flock		fl;

	fl = (t_flock)
	{
		.l_type = xft_f_rdlck,
		.l_whence = xft_seek_set,
		.l_start = 0,
		.l_len = 0,
	};
	return (xft_fcntl((t_u32a)fd, xft_f_setlkw, &fl));
}

t_xft_sysres	xft_unlockf(int fd)
{
	t_flock		fl;

	fl = (t_flock)
	{
		.l_type = xft_f_unlck,
		.l_whence = xft_seek_set,
		.l_start = 0,
		.l_len = 0,
	};
	return (xft_fcntl((t_u32a)fd, xft_f_setlk, &fl));
}

# endif

#endif
