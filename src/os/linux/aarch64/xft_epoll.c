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

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_xft_sysres	xft_epoll_create(int flags, int *restrict const epfd)
{
	register long x8	__asm__("x8");
	register long x0	__asm__("x0");
	t_u64a				r;

	x8 = xft_sys_epoll_create1;
	x0 = flags;
	__asm__ volatile (
		"svc #0"
		: "+r"(x0)
		: "r"(x8)
		: "memory", "cc"
	);
	*epfd = (int)xft_tern(x0 < 0, (t_u64a)-1, (t_u64a)x0);
	r = xft_tern(x0 < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(x0 == -xft_eintr || x0 == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

__attribute__((__always_inline__, __used__))
inline t_xft_sysres	xft_epoll_ctl(int epfd, int op, int fd,
	t_epoll_event *event)
{
	register long x0	__asm__("x0");
	register long x1	__asm__("x1");
	register long x2	__asm__("x2");
	register long x3	__asm__("x3");
	t_u64a				r;

	x1 = op;
	x2 = fd;
	x3 = (long)event;
	x0 = epfd;
	__asm__ volatile (
		"mov x8, %[nr]\n\t"
		"svc #0"
		: "+r"(x0)
		: "r"(x1), "r"(x2), "r"(x3), [nr] "i"(xft_sys_epoll_ctl)
		: "memory", "cc", "x8"
	);
	r = xft_tern(x0 < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(x0 == -xft_eintr || x0 == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

__attribute__((__nonnull__(2, 4), __always_inline__, __used__))
inline t_xft_sysres	xft_epoll_wait(int epfd, t_epoll_event *restrict events,
	int timeout, int *restrict const ready)
{
	t_u64a	args[6];
	t_i64a	ret;
	t_u64a	r;

	args[0] = (t_u64a)epfd;
	args[1] = (t_u64a)events;
	args[2] = (long)*ready;
	args[3] = (t_u64a)timeout;
	args[4] = 0;
	args[5] = 0;
	ret = xft_syscall6(xft_sys_epoll_pwait, args);
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
