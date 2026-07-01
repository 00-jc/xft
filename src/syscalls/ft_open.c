/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
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

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_open(const char *restrict path, int flags)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_OPEN),
		"D"(path),
		"S"(flags)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#else

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_open(const char *restrict path, int flags)
{
	return ((int)syscall(SYS_OPEN, path, flags));
}

#endif
