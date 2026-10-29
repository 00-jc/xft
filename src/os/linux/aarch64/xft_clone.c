/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_clone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 00:53:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i32	xft_clone(const t_clone_arg *__restrict__ const args)
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
		"mov x9, %[fn]\n\tmov x10, %[arg]\n\tmov x8, %[nr]\n\t"
		"svc #0\n\tcbnz x0, 1f\n\t"
		"mov x29, xzr\n\tmov x0, x10\n\tblr x9\n\t"
		"mov x8, %[ex]\n\tsvc #0\n\t1:"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), "r"(x4), [nr] "i"(xft_sys_clone),
		[fn] "r"(args->fn), [arg] "r"(args->arg), [ex] "i"(xft_sys_exit)
		: "memory", "cc", "x8", "x9", "x10"
	);
	return ((t_i32)xft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0));
}

# endif

#endif
