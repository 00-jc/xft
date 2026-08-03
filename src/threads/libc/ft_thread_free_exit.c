/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_free_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/02 20:50:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "private/ft_p_syscalls.h"
#include "syscalls.h"
#include "signals.h"
#include "threads.h"
#include "private/ft_p_rt.h"

#ifdef FT_REQUIRE_LIBC

__attribute__((__nonnull__(1), __noreturn__))
void	ft_thread_free_exit(t_thread_completion	*__restrict__ const comp)
{
	static const t_sigset	new = {{~0}};

	if (comp->mapped.mem == nullptr)
		__builtin_unreachable();
	ft_set_tid_address(nullptr);
	ft_sigprocmask(FT_BLOCK, (t_any) & new, nullptr);
	ft_munmap(comp->mapped.mem, comp->mapped.size);
	syscall(SYS_EXIT, 0);
	__builtin_unreachable();
}

#endif
