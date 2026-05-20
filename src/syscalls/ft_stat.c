/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 04:03:47 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/20 15:29:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"

#ifdef __x86_64__

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_stat(const char *restrict path, struct stat *statbuf)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_stat),
		"D"(path),
		"S"(statbuf)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#else

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_stat(const char *restrict path, struct stat *statbuf)
{
	return ((int)syscall(SYS_newfstatat, AT_FDCWD, path, statbuf, 0));
}

#endif
