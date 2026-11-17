/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_madvise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(1)))
t_xft_sysres	xft_madvise(t_any addr, t_size size, int advice)
{
	t_ssize	ret;
	t_u64a	r;

	ret = syscall(SYS_madvise, addr, size, advice);
	r = xft_tern(errno == EINTR || errno == EAGAIN, xft_sys_repeat, xft_sys_ko);
	r = xft_tern(ret < 0, r, xft_sys_ok);
	return ((t_xft_sysres)r);
}

# endif

#endif
