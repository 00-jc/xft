/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:58:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 14:15:51 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__nonnull__(2), __always_inline__))
inline t_ssize	ft_read(int fd, t_u8 *restrict const buffer, t_size len)
{
	t_ssize		ret;

	__asm__(
		"syscall"
		: "=a"(ret)
		: "0"(SYS_READ),
		"D"(fd),
		"S"(buffer),
		"d"(len)
		: "rcx", "r11", "memory"
		);
	return (ret);
}

#else

__attribute__((__nonnull__(2), __always_inline__))
inline t_ssize	ft_read(int fd, t_u8 *restrict const buffer, t_size len)
{
	return (syscall(SYS_READ, fd, buffer, len));
}

#endif
