/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_thread_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:38:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/threads.h>
#include <xft/types/signal_types.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __unused__, __flatten__))
static inline void	xft__set_tid_address(t_any address)
{
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");

	x8 = xft_sys_set_tid_address;
	x0 = (long)address;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8)
		: "memory", "cc"
	);
}

__attribute__((__always_inline__, __unused__, __flatten__))
static inline void	xft__block_signals(void)
{
	t_u64a				all;
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x3	__asm__("x3");

	all = ~(t_u64a)0;
	x8 = xft_sys_rt_sigprocmask;
	x0 = XFT_BLOCK;
	x1 = (long)&all;
	x3 = XFT_SIGSET_SIZE;
	__asm__ volatile (
		"mov x2, xzr\n\tsvc #0"
		: "+r"(x0)
		: "r"(x8), "r"(x1), "r"(x3)
		: "memory", "cc", "x2"
	);
}

__attribute__((__always_inline__, __unused__, __flatten__, __noreturn__))
static inline void	xft__unmap_exit(t_any base, t_size size)
{
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");

	x0 = (long)base;
	x1 = (long)size;
	__asm__ volatile (
		"mov x8, %[un]\n\tsvc #0\n\tmov x0, xzr\n\tmov x8, %[ex]\n\tsvc #0"
		: "+r"(x0)
		: "r"(x1), [un] "i"(xft_sys_munmap), [ex] "i"(xft_sys_exit)
		: "memory", "cc", "x8"
	);
	__builtin_unreachable();
}

__attribute__((__nonnull__(1), __noreturn__, __flatten__))
void	xft_thread_destroy(t_thread_instance *__restrict__ const instance)
{
	xft__set_tid_address(nullptr);
	xft__block_signals();
	xft__unmap_exit(instance->base, instance->size);
}

# endif

#endif
