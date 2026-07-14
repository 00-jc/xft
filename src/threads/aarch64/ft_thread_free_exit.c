/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_free_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 01:30:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "private/ft_p_syscalls.h"
#include "syscalls.h"
#include "signals.h"
#include "threads.h"
#include "private/ft_p_rt.h"

#ifdef __aarch64__

/*
 *	ft_exit() only has an out-of-line declaration in syscalls.h, so calls
 *	to it from other translation units are real `call` instructions: the
 *	always_inline on its definition never reaches this call site if not on lto.
 *	Once the stack behind `comp` is unmapped below, this thread cannot return
 *	through a call frame anymore, so the final syscall has to be emitted right
 *	here.
 */
__attribute__((__cold__, __always_inline__, __noreturn__, __unused__))
static inline void	ft__exit(int status)
{
	const register long x8	__asm__("x8") = SYS_EXIT;
	const register long x0	__asm__("x0") = status;

	__asm__ volatile (
		"svc #0"
		:
		: "r"(x8), "r"(x0)
		: "memory", "cc"
	);
	__builtin_unreachable();
}

__attribute__((__nonnull__(1), __noreturn__))
void	ft_thread_free_exit(t_thread_completion	*__restrict__ const comp)
{
	static const t_sigset	new = {~0};

	if (comp->mapped.mem == nullptr)
		__builtin_unreachable();
	ft_set_tid_address(nullptr);
	ft_sigprocmask(FT_BLOCK, (t_any) & new, nullptr);
	ft_munmap(comp->mapped.mem, comp->mapped.size);
	ft__exit(0);
}

#endif
