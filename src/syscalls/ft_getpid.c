/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 22:56:30 by username          #+#    #+#             */
/*   Updated: 2026/06/28 22:56:35 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__always_inline__))
inline int	ft_getpid(void)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_GETPID)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#else

__attribute__((__always_inline__))
inline int	ft_getpid(void)
{
	return ((int)syscall(SYS_GETPID));
}

#endif
