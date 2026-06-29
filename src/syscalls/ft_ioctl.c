/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ioctl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:16:00 by username          #+#    #+#             */
/*   Updated: 2026/06/28 17:16:00 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__always_inline__))
inline int	ft_ioctl(int fd, t_u64a request, t_u64a arg)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_IOCTL),
		"D"(fd),
		"S"(request),
		"d"(arg)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#else

__attribute__((__always_inline__))
inline int	ft_ioctl(int fd, t_u64a request, t_u64a arg)
{
	return ((int)syscall(SYS_IOCTL, fd, request, arg));
}

#endif
