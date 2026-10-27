/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_futex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 12:49:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i64a	xft_futex_wait(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	t_u64a	args[6];
	t_i64a	ret;

	args[0] = (t_u64a)uaddr;
	args[1] = xft_futex_op_wait;
	args[2] = val;
	args[3] = 0;
	args[4] = 0;
	args[5] = 0;
	ret = xft_syscall6(xft_sys_futex, args);
	return ((t_i64a)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i64a	xft_futex_wake(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	t_u64a	args[6];
	t_i64a	ret;

	args[0] = (t_u64a)uaddr;
	args[1] = xft_futex_op_wake;
	args[2] = val;
	args[3] = 0;
	args[4] = 0;
	args[5] = 0;
	ret = xft_syscall6(xft_sys_futex, args);
	return ((t_i64a)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

# endif

#endif
