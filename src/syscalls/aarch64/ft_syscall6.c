/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscall6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 12:52:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_syscalls.h"

#if defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

/*
 *	aarch64 has no single-register asm constraints (unlike x86_64's
 *	D/S/d), so syscalls needing more than 5 registers (nr + 5 args)
 *	would need more pinned locals than norm allows. This naked helper
 *	takes the number and an array of up to 6 args and does the register
 *	shuffle itself, in: x0 = nr, x1 = args.
 */

__attribute__((naked))
long	ft_syscall6(long nr, const long args[6])
{
	__asm__ volatile (
		"mov x9, x1\n"
		"mov x8, x0\n"
		"ldr x0, [x9, #0]\n"
		"ldr x1, [x9, #8]\n"
		"ldr x2, [x9, #16]\n"
		"ldr x3, [x9, #24]\n"
		"ldr x4, [x9, #32]\n"
		"ldr x5, [x9, #40]\n"
		"svc #0\n"
		"ret\n"
	);
}

#endif
