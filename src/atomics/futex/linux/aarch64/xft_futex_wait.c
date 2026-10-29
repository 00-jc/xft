/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_futex_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 21:10:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 21:10:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/atomics.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_futex_wait(t_atomic32 *__restrict__ const atomic,
	t_u32a value_to_wait)
{
	t_u64a	args[6];

	args[0] = (t_u64a)atomic;
	args[1] = xft_futex_op_wait;
	args[2] = value_to_wait;
	args[3] = 0;
	args[4] = 0;
	args[5] = 0;
	xft_syscall6(xft_sys_futex, args);
}

# endif

#endif
