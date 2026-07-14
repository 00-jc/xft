/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_futex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 21:04:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 13:14:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "types/atomic_types.h"

#ifdef FT_REQUIRE_LIBC

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wait(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	return (syscall(SYS_FUTEX, uaddr, FUTEX_WAIT,
			val, NULL, NULL, 0));
}

__attribute__((__nonnull__(1), __always_inline__))
inline long	ft_futex_wake(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	return (syscall(SYS_FUTEX, uaddr, FUTEX_WAKE,
			val, NULL, NULL, 0));
}

#endif
