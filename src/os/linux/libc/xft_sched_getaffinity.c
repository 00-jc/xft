/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sched_getaffinity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 11:21:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 11:28:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(3, 4), __always_inline__, __used__))
inline t_xft_sysres	xft_sched_getaffinity(t_i32a pid, t_size cpusetsize,
		const t_u64a *__restrict__ mask,
	t_size *__restrict__ const written)
{
	t_ssize	ret;
	t_u64a	r;

	ret = syscall(SYS_sched_getaffinity, pid, cpusetsize, mask);
	*written = (t_size)xft_tern(ret < 0, 0, (t_u64a)ret);
	r = xft_tern(errno == EINTR || errno == EAGAIN, xft_sys_repeat, xft_sys_ko);
	r = xft_tern(ret < 0, r, xft_sys_ok);
	return ((t_xft_sysres)r);
}

# endif

#endif
