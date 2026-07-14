/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_futex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 12:49:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "types/atomic_types.h"
#include "private/ft_p_syscalls.h"

#ifdef __aarch64__

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wait(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	long	args[6];

	args[0] = (long)uaddr;
	args[1] = FUTEX_WAIT;
	args[2] = val;
	args[3] = 0;
	args[4] = 0;
	args[5] = 0;
	return (ft_syscall6(SYS_FUTEX, args));
}

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wake(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	long	args[6];

	args[0] = (long)uaddr;
	args[1] = FUTEX_WAKE;
	args[2] = val;
	args[3] = 0;
	args[4] = 0;
	args[5] = 0;
	return (ft_syscall6(SYS_FUTEX, args));
}

#endif
