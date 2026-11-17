/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sendto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 17:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_xft_sysres	xft_sendto(int fd, t_iovec *restrict buf,
	t_xft_msg_opts opts, const t_sockaddr_in6 *restrict dest)
{
	t_u64a	args[6];
	t_i64a	ret;
	t_u64a	r;

	args[0] = (t_u64a)fd;
	args[1] = (t_u64a)buf->mem;
	args[2] = buf->size;
	args[3] = opts.flags | xft_msg_nosignal;
	args[4] = (t_u64a)dest;
	args[5] = xft_tern(dest && dest->sin6_family == xft_af_inet6,
			sizeof(t_sockaddr_in6), sizeof(t_sockaddr_in));
	ret = xft_syscall6(xft_sys_sendto, args);
	buf->size = (t_size)xft_tern(ret < 0, 0, (t_u64a)ret);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
