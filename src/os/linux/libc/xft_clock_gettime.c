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

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_xft_sysres	xft_clock_gettime(t_timespec *__restrict__ const ts)
{
	t_ssize	ret;
	t_u64a	r;

	ret = clock_gettime(CLOCK_MONOTONIC, ts);
	r = xft_tern(errno == EINTR || errno == EAGAIN, xft_sys_repeat, xft_sys_ko);
	r = xft_tern(ret < 0, r, xft_sys_ok);
	return ((t_xft_sysres)r);
}

# endif

#endif
