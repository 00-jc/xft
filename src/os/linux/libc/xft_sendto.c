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

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_result	xft_sendto(int fd, t_iovec *restrict buf,
	t_xft_msg_opts opts, const t_sockaddr_in6 *restrict dest)
{
	t_ssize	ret;

	ret = syscall(SYS_sendto, fd, buf->mem, buf->size,
			opts.flags | xft_msg_nosignal, dest,
			(long)xft_tern(dest && dest->sin6_family == xft_af_inet6,
				sizeof(t_sockaddr_in6), sizeof(t_sockaddr_in)));
	buf->size = (t_size)xft_tern(ret < 0, 0, (t_u64a)ret);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

# endif

#endif
