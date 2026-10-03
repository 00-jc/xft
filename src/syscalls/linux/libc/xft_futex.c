/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_futex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 21:04:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 13:14:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "types/atomic_types.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i64a	xft_futex_wait(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	return (syscall(SYS_FUTEX, uaddr, FUTEX_WAIT,
			val, (t_any)0, (t_any)0, 0));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i64a	xft_futex_wake(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	return (syscall(SYS_FUTEX, uaddr, FUTEX_WAKE,
			val, (t_any)0, (t_any)0, 0));
}

# endif

#endif
