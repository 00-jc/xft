/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_futex_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 21:10:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 21:10:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/atomics.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_futex_wait(t_atomic32 *__restrict__ const atomic,
	t_u32a value_to_wait)
{
	long					ret;
	register long r8		__asm__("r8");
	register long r9		__asm__("r9");
	register long r10		__asm__("r10");

	r8 = 0;
	r9 = 0;
	r10 = 0;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_futex),
		"D"(atomic),
		"S"((long)xft_futex_op_wait),
		"d"((long)value_to_wait),
		"r"(r10),
		"r"(r8),
		"r"(r9)
		: "rcx", "r11", "memory"
	);
	(void)ret;
}

# endif

#endif
