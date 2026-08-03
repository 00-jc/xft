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
#include "bmi.h"
#include "private/ft_p_syscalls.h"

#if defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__))
inline t_i32	ft_clone(const t_clone_arg *__restrict__ const args)
{
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	register long x3	__asm__("x3");
	register long x4	__asm__("x4");

	x1 = (long)args->stack;
	x2 = (long)args->ptid;
	x3 = (long)args->tls;
	x4 = (long)args->ctid;
	x0 = (long)args->flags;
	__asm__ volatile (
		"mov x8, %[nr]\n\t"
		"svc #0"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), "r"(x4), [nr] "i"(SYS_CLONE)
		: "memory", "cc", "x8"
	);
	return ((t_i32)ft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

#endif
