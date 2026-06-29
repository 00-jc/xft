/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
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
