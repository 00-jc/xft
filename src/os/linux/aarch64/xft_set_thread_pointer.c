/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_set_thread_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 15:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 15:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline int	xft_set_thread_pointer(t_uptr tp)
{
	register long x0	__asm__("x0");

	x0 = (long)tp;
	__asm__ volatile (
		"msr tpidr_el0, %[tp]"
		:
		: [tp] "r"(x0)
		: "memory"
	);
	return (0);
}

# endif

#endif
