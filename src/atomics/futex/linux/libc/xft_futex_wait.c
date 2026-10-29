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

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_futex_wait(t_atomic32 *__restrict__ const atomic,
	t_u32a value_to_wait)
{
	syscall(SYS_futex, atomic, xft_futex_op_wait,
		value_to_wait, (t_any)0, (t_any)0, 0);
}

# endif

#endif
