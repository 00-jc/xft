/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_lockf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_i32a	xft_fcntl(t_u32a fd, t_u32a cmd,
		const t_flock *restrict const arg)
{
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");

	x8 = xft_sys_fcntl;
	x1 = cmd;
	x2 = (long)arg;
	x0 = fd;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	return ((t_i32a)xft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

t_i32a	xft_lockf(int fd)
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

t_i32a	xft_unlockf(int fd)
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
