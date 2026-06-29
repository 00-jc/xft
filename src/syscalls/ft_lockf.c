/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lockf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 23:58:49 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 15:12:45 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((nonnull(3), __always_inline__))
inline t_u32a	ft_fcntl(t_u32a fd, t_u32a cmd,
		const t_flock *restrict const arg)
{
	t_u32a	ret;

	__asm__ volatile (
		"syscall"
		: "=a" (ret)
		: "0" (SYS_FCNTL),
		"D" (fd),
		"S" (cmd),
		"d" (arg)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#else

__attribute__((nonnull(3), __always_inline__))
inline t_u32a	ft_fcntl(t_u32a fd, t_u32a cmd,
	const t_flock *restrict const arg)
{
	return ((t_u32a)syscall(SYS_FCNTL, fd, cmd, arg));
}

#endif

t_u32a	ft_lockf(int fd)
{
	t_flock		fl;

	fl = (t_flock)
	{
		.l_type = F_RDLCK,
		.l_whence = SEEK_SET,
		.l_start = 0,
		.l_len = 0,
	};
	return (ft_fcntl((t_u32a)fd, F_SETLKW, &fl));
}

t_u32a	ft_unlockf(int fd)
{
	t_flock		fl;

	fl = (t_flock)
	{
		.l_type = F_UNLCK,
		.l_whence = SEEK_SET,
		.l_start = 0,
		.l_len = 0,
	};
	return (ft_fcntl((t_u32a)fd, F_SETLK, &fl));
}
