/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 00:53:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __aarch64__

__attribute__((__nonnull__(1), __always_inline__))
inline t_i32	ft_clone(const t_clone_arg *__restrict__ const args)
{
	register long x0		__asm__("x0");
	const register long x1	__asm__("x1") = (long)args->stack;
	const register long x2	__asm__("x2") = (long)args->ptid;
	const register long x3	__asm__("x3") = (long)args->tls;
	const register long x4	__asm__("x4") = (long)args->ctid;

	x0 = (long)args->flags;
	__asm__ volatile (
		"mov x8, %[nr]\n\t"
		"svc #0"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), "r"(x4), [nr] "i"(SYS_CLONE)
		: "memory", "cc", "x8"
	);
	return ((t_i32)x0);
}

#endif
