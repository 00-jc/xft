/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/30 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_xft_sysres	xft_fork(t_i32 *restrict const pid)
{
	t_ssize	ret;
	t_u64a	r;

	ret = syscall(SYS_clone, XFT_SIGCHLD, 0, 0, 0, 0);
	*pid = (t_i32)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	r = xft_tern(errno == EINTR || errno == EAGAIN, xft_sys_repeat, xft_sys_ko);
	r = xft_tern(ret < 0, r, xft_sys_ok);
	return ((t_xft_sysres)r);
}

# endif

#endif
