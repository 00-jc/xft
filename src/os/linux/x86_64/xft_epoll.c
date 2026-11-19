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

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_result	xft_epoll_create(int flags, int *restrict const epfd)
{
	int		ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_epoll_create1),
		"D"((long)flags)
		: "rcx", "r11", "memory"
	);
	*epfd = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

__attribute__((__always_inline__, __used__))
inline t_result	xft_epoll_ctl(int epfd, int op, int fd,
	t_epoll_event *event)
{
	int					ret;
	register long r10	__asm__("r10");

	r10 = (long)event;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_epoll_ctl),
		"D"(epfd),
		"S"((long)op),
		"d"((long)fd),
		"r"(r10)
		: "rcx", "r11", "memory"
	);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

__attribute__((__nonnull__(2, 4), __always_inline__, __used__))
inline t_result	xft_epoll_wait(int epfd, t_epoll_event *restrict events,
	int timeout, int *restrict const ready)
{
	int					ret;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");

	r10 = (long)timeout;
	r8 = 0;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_epoll_pwait),
		"D"(epfd),
		"S"(events),
		"d"((long)*ready),
		"r"(r10),
		"r"(r8)
		: "rcx", "r11", "memory"
	);
	*ready = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

__attribute__((__always_inline__, __used__))
inline t_result	xft_epoll_close(int epfd)
{
	return (xft_close(epfd));
}

# endif

#endif
