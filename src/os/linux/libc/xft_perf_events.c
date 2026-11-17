/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_perf_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/types/linux_types.h>
#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(1, 3), __always_inline__, __used__))
inline t_xft_sysres	xft_perf_event_open(const t_perf_event_attr *restrict attr,
	int group_fd, int *restrict const fd)
{
	t_ssize	ret;
	t_u64a	r;

	ret = syscall(SYS_perf_event_open, attr, 0, -1, group_fd,
			xft_perf_flag_fd_cloexec);
	*fd = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	r = xft_tern(errno == EINTR || errno == EAGAIN, xft_sys_repeat, xft_sys_ko);
	r = xft_tern(ret < 0, r, xft_sys_ok);
	return ((t_xft_sysres)r);
}

# endif

#endif
