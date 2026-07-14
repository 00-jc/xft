/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 00:53:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __x86_64__

__attribute__((__nonnull__(1), __always_inline__))
inline t_i32	ft_clone(const t_clone_arg *__restrict__ const args)
{
	t_i32						ret;
	const register long r10		__asm__("r10") = (long)args->ctid;
	const register long r8		__asm__("r8") = (long)args->tls;

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
	return (ret);
}

#endif
