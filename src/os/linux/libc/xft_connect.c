/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 16:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_xft_sysres	xft_connect(int fd, const t_sockaddr *addr, t_u32a addrlen)
{
	t_ssize	ret;
	t_u64a	r;

	ret = syscall(SYS_connect, fd, addr, addrlen);
	r = xft_tern(errno == EAGAIN, xft_sys_repeat, xft_sys_ko);
	r = xft_tern(errno == EINTR || errno == EINPROGRESS, xft_sys_pending, r);
	r = xft_tern(ret < 0, r, xft_sys_ok);
	return ((t_xft_sysres)r);
}

# endif

#endif
