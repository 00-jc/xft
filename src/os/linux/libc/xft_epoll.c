/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_epoll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 15:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_result	xft_epoll_create(int flags, int *restrict const epfd)
{
	t_ssize	ret;

	ret = syscall(SYS_epoll_create1, flags);
	*epfd = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

__attribute__((__always_inline__, __used__))
inline t_result	xft_epoll_ctl(int epfd, int op, int fd,
	t_epoll_event *event)
{
	t_ssize	ret;

	ret = syscall(SYS_epoll_ctl, epfd, op, fd, event);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

__attribute__((__nonnull__(2, 4), __always_inline__, __used__))
inline t_result	xft_epoll_wait(int epfd, t_epoll_event *restrict events,
	int timeout, int *restrict const ready)
{
	t_ssize	ret;

	ret = syscall(SYS_epoll_pwait, epfd, events, *ready, timeout, (t_any)0);
	*ready = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

__attribute__((__always_inline__, __used__))
inline t_result	xft_epoll_close(int epfd)
{
	return (xft_close(epfd));
}

# endif

#endif
