/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_io_uring_enter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/linux/uring.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_result	xft_io_uring_enter(int fd, t_io_uring_enter enter,
	int *restrict const submitted)
{
	t_u64a	args[6];
	t_i64a	ret;

	args[0] = (t_u64a)fd;
	args[1] = (t_u64a)enter.to_submit;
	args[2] = (t_u64a)enter.min_complete;
	args[3] = (t_u64a)enter.flags;
	args[4] = (t_u64a)enter.arg;
	args[5] = (t_u64a)enter.argsz;
	ret = xft_syscall6(xft_sys_io_uring_enter, args);
	*submitted = (int)ret;
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

# endif

#endif
