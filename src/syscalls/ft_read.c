/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:58:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 20:59:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"

#ifdef __x86_64__

__attribute__((__nonnull__(2), __always_inline__))
inline ssize_t	ft_read(int fd, t_u8 *restrict const buffer, size_t len)
{
	ssize_t		ret;

	__asm__(
		"syscall"
		: "=a"(ret)
		: "0"(SYS_read),
		"D"(fd),
		"S"(buffer),
		"d"(len)
		: "rcx", "r11", "memory"
		);
	return (ret);
}

#else

__attribute__((__nonnull__(2), __always_inline__))
inline ssize_t	ft_read(int fd, t_u8 *restrict const buffer, size_t len)
{
	return (syscall(SYS_read, fd, buffer, len));
}

#endif
