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

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(4), __always_inline__, __used__))
inline t_result	xft_accept(int fd, int flags, t_sockaddr_in6 *restrict addr,
	int *restrict const conn)
{
	t_ssize	ret;
	t_u32a	len;

	len = sizeof(t_sockaddr_in6);
	ret = syscall(SYS_accept4, fd, addr, &len, flags);
	*conn = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

# endif

#endif
