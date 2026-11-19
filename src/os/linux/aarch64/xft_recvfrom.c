/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_recvfrom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 17:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_result	xft_recvfrom(int fd, t_iovec *restrict buf,
	t_xft_msg_opts opts, t_sockaddr_in6 *restrict from)
{
	t_u64a	args[6];
	t_i64a	ret;
	t_u32a	len;

	len = sizeof(t_sockaddr_in6);
	args[0] = (t_u64a)fd;
	args[1] = (t_u64a)buf->mem;
	args[2] = buf->size;
	args[3] = opts.flags;
	args[4] = (t_u64a)from;
	args[5] = (long)&len;
	ret = xft_syscall6(xft_sys_recvfrom, args);
	buf->size = (t_size)xft_tern(ret < 0, 0, (t_u64a)ret);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

# endif

#endif
