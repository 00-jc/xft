/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mprotect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_syscalls.h"
#include "syscalls.h"

#ifdef __aarch64__

__attribute__((__nonnull__(1)))
int	ft_mprotect(t_any addr, t_size size, int prot)
{
	const register long x8	__asm__("x8") = SYS_MPROTECT;
	register long x0		__asm__("x0");
	const register long x1	__asm__("x1") = (long)size;
	const register long x2	__asm__("x2") = prot;

	x0 = (long)addr;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x2)
		: "memory", "cc"
	);
	return ((int)x0);
}

#endif
