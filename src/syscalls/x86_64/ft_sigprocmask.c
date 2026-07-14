/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigprocmask.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:17:37 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/08 18:37:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_syscalls.h"
#include "types/signal_types.h"

#ifdef __x86_64__

__attribute__((__always_inline__))
inline int	ft_sigprocmask(t_u32a flags, t_sigset *__restrict__ const set,
	t_sigset *__restrict__ const oldest)
{
	int		ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_RT_SIGPROCMASK),
		"D"(flags),
		"S"(set),
		"d"(oldest)
		: "r11", "rcx", "memory"
	);
	return (ret);
}

#endif
