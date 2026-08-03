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

#if defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__nonnull__(1, 2), __always_inline__))
inline int	ft_execve(const char *restrict path,
		char *const *argv, char *const *envp)
{
	register long x8	__asm__("x8") = SYS_EXECVE;
	register long x0		__asm__("x0");
	register long x1	__asm__("x1") = (long)argv;
	register long x2	__asm__("x2") = (long)envp;

	x0 = (long)path;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	return ((int)ft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

#endif
