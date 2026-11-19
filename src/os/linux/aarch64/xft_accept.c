/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_accept.c                                       :+:      :+:    :+:   */
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

__attribute__((__nonnull__(4), __always_inline__, __used__))
inline t_result	xft_accept(int fd, int flags, t_sockaddr_in6 *restrict addr,
	int *restrict const conn)
{
	t_u64a	args[6];
	t_i64a	ret;
	t_u32a	len;

	len = sizeof(t_sockaddr_in6);
	args[0] = (t_u64a)fd;
	args[1] = (t_u64a)addr;
	args[2] = (long)&len;
	args[3] = (t_u64a)flags;
	args[4] = 0;
	args[5] = 0;
	ret = xft_syscall6(xft_sys_accept4, args);
	*conn = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

# endif

#endif
