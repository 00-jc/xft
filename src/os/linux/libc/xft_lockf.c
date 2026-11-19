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

# ifdef XFT_REQUIRE_LIBC

#  ifdef SYS_fcntl

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_result	xft_fcntl(t_u32a fd, t_u32a cmd,
	const t_flock *restrict const arg)
{
	t_ssize	ret;

	ret = syscall(SYS_fcntl, fd, cmd, arg);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

#  else

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_result	xft_fcntl(t_u32a fd, t_u32a cmd,
	const t_flock *restrict const arg)
{
	t_ssize	ret;

	ret = fcntl((t_i32a)fd, (t_i32a)cmd, arg);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

#  endif

t_result	xft_lockf(int fd)
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

t_result	xft_unlockf(int fd)
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
