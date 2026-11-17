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
inline t_xft_sysres	xft_epoll_create(int flags, int *restrict const epfd)
{
	int		ret;
	t_u64a	r;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_epoll_create1),
		"D"((long)flags)
		: "rcx", "r11", "memory"
	);
	*epfd = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

__attribute__((__always_inline__, __used__))
inline t_xft_sysres	xft_epoll_ctl(int epfd, int op, int fd,
	t_epoll_event *event)
{
	int					ret;
	register long r10	__asm__("r10");
	t_u64a				r;

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
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

__attribute__((__nonnull__(2, 4), __always_inline__, __used__))
inline t_xft_sysres	xft_epoll_wait(int epfd, t_epoll_event *restrict events,
	int timeout, int *restrict const ready)
{
	int					ret;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");
	t_u64a				r;

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
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

__attribute__((__always_inline__, __used__))
inline t_xft_sysres	xft_epoll_close(int epfd)
{
	return (xft_close(epfd));
}

# endif

#endif
