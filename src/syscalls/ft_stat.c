/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 04:03:47 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 14:16:23 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_stat(const char *restrict path, t_stat *statbuf)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_STAT),
		"D"(path),
		"S"(statbuf)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#else

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_stat(const char *restrict path, t_stat *statbuf)
{
	return ((int)syscall(SYS_NEWFSTATAT, AT_FDCWD, path, statbuf, 0));
}

#endif
