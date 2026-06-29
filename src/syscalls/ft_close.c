/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:36:00 by username          #+#    #+#             */
/*   Updated: 2026/06/28 17:36:00 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__always_inline__))
inline int	ft_close(int fd)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_CLOSE),
		"D"(fd)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#else

__attribute__((__always_inline__))
inline int	ft_close(int fd)
{
	return ((int)syscall(SYS_CLOSE, fd));
}

#endif
