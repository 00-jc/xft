/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
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

__attribute__((__nonnull__(2), __always_inline__))
inline t_ssize	ft_write(int fd, t_u8 *restrict const buffer, t_size len)
{
	t_ssize		ret;

	__asm__(
		"syscall"
		: "=a"(ret)
		: "0"(SYS_WRITE),
		"D"(fd),
		"S"(buffer),
		"d"(len)
		: "rcx", "r11", "memory"
		);
	return (ret);
}

#else

__attribute__((__nonnull__(2), __always_inline__))
inline t_ssize	ft_write(int fd, t_u8 *restrict const buffer, t_size len)
{
	return (syscall(SYS_WRITE, fd, buffer, len));
}

#endif
