/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/30 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "private/ft_p_syscalls.h"

#if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__nonnull__(1, 2), __always_inline__))
inline int	ft_execve(const char *restrict path,
		char *const *argv, char *const *envp)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_EXECVE),
		"D"(path),
		"S"(argv),
		"d"(envp)
		: "rcx", "r11", "memory"
	);
	return ((int)ft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

#endif
