/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lockf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __aarch64__

__attribute__((nonnull(3), __always_inline__))
inline t_u32a	ft_fcntl(t_u32a fd, t_u32a cmd,
		const t_flock *restrict const arg)
{
	const register long x8	__asm__("x8") = SYS_FCNTL;
	register long x0		__asm__("x0");
	const register long x1	__asm__("x1") = cmd;
	const register long x2	__asm__("x2") = (long)arg;

	x0 = fd;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	return ((t_u32a)x0);
}

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

#endif
