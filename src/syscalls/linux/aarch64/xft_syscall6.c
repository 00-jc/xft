/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_syscall6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 12:52:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((naked, __nonnull__(2)))
t_i64a	xft_syscall6(t_u64a nr, const t_u64a args[6])
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

# endif

#endif
