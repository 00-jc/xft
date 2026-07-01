/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ioctl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
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
