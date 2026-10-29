/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_thread_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:40:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/threads.h>
#include <xft/types/signal_types.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __unused__, __flatten__))
static inline void	xft__set_tid_address(t_any address)
{
	t_i64a	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_set_tid_address), "D"(address)
		: "rcx", "r11", "memory"
	);
	(void)ret;
}

__attribute__((__always_inline__, __unused__, __flatten__))
static inline void	xft__block_signals(void)
{
	t_u64a				all;
	t_i64a				ret;
	register long r10	__asm__("r10");

	all = ~(t_u64a)0;
	r10 = XFT_SIGSET_SIZE;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_rt_sigprocmask), "D"((long)XFT_BLOCK),
		"S"((long)&all), "d"((long)0), "r"(r10)
		: "rcx", "r11", "memory"
	);
	(void)ret;
}

__attribute__((__always_inline__, __unused__, __flatten__, __noreturn__))
static inline void	xft__unmap_exit(t_any base, t_size size)
{
	__asm__ volatile (
		"syscall\n\txor %%edi, %%edi\n\tmov %[ex], %%eax\n\tsyscall"
		:
		: "a"((long)xft_sys_munmap), "D"(base), "S"(size),
		[ex] "i"(xft_sys_exit)
		: "rcx", "r11", "memory"
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
