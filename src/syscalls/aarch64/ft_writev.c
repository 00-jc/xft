/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writev.c                                        :+:      :+:    :+:   */
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

__attribute__((__nonnull__(2), __always_inline__))
inline t_ssize	ft_writev(int fd, t_iovec *restrict const buffers, t_size len)
{
	const register long x8	__asm__("x8") = SYS_WRITEV;
	register long x0		__asm__("x0");
	const register long x1	__asm__("x1") = (long)buffers;
	const register long x2	__asm__("x2") = (long)len;

	x0 = fd;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	return (x0);
}

#endif
