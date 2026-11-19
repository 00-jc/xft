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

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_result	xft_io_uring_enter(int fd, t_io_uring_enter enter,
	int *restrict const submitted)
{
	t_ssize	ret;

	ret = syscall(SYS_io_uring_enter, fd, enter.to_submit, enter.min_complete,
			enter.flags, enter.arg, enter.argsz);
	*submitted = (int)ret;
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

# endif

#endif
