/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __aarch64__

__attribute__((__always_inline__))
inline int	ft_getpid(void)
{
	const register long x8	__asm__("x8") = SYS_GETPID;
	register long x0		__asm__("x0");

	__asm__ volatile (
		"svc #0"
		: "=r"(x0)
		: "r"(x8)
		: "memory", "cc"
	);
	return ((int)x0);
}

#endif
