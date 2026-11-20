/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_signalfd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/20 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(2, 4), __always_inline__, __used__))
inline t_result	xft_signalfd(int fd, const t_u64a *mask, int flags,
	int *restrict const sfd)
{
	t_ssize	ret;

	ret = syscall(SYS_signalfd4, fd, mask, (long)XFT_SIGSET_SIZE, flags);
	*sfd = (int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

# endif

#endif
