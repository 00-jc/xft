/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_clock_gettime.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_i64a	xft_clock_gettime(t_timespec *__restrict__ const ts)
{
	return ((t_i64a)syscall(SYS_CLOCK_GETTIME, 1, ts));
}

# endif

#endif
