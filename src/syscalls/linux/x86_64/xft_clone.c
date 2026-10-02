/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_clone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:28:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i32	xft_clone(const t_clone_arg *__restrict__ const args)
{
	t_i32						ret;
	register long r10			__asm__("r10");
	register long r8			__asm__("r8");

	r10 = (long)args->ctid;
	r8 = (long)args->tls;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_CLONE),
		"D"((long)args->flags),
		"S"((long)args->stack),
		"d"((long)args->ptid),
		"r"(r10), "r"(r8)
		: "rcx", "r11", "memory"
	);
	return ((t_i32)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

# endif

#endif
