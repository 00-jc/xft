/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_perf_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/types/linux_types.h>
#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1, 3), __always_inline__, __used__))
inline t_xft_sysres	xft_perf_event_open(const t_perf_event_attr *restrict attr,
	int group_fd, int *restrict const fd)
{
	t_u64a	args[6];
	t_i64a	ret;
	t_u64a	r;

	args[0] = (t_u64a)attr;
	args[1] = 0;
	args[2] = -1;
	args[3] = group_fd;
	args[4] = xft_perf_flag_fd_cloexec;
	args[5] = 0;
	ret = xft_syscall6(xft_sys_perf_event_open, args);
	*fd = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
