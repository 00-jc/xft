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
#include "bmi.h"
#include "types/atomic_types.h"
#include "private/ft_p_syscalls.h"

#if defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wait(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	long	args[6];
	long	ret;

	args[0] = (long)uaddr;
	args[1] = FUTEX_WAIT;
	args[2] = val;
	args[3] = 0;
	args[4] = 0;
	args[5] = 0;
	ret = ft_syscall6(SYS_FUTEX, args);
	return ((long)ft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wake(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	long	args[6];
	long	ret;

	args[0] = (long)uaddr;
	args[1] = FUTEX_WAKE;
	args[2] = val;
	args[3] = 0;
	args[4] = 0;
	args[5] = 0;
	ret = ft_syscall6(SYS_FUTEX, args);
	return ((long)ft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

#endif
