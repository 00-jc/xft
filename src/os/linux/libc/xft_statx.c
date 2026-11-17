/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_statx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 22:41:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/27 22:41:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(1, 4), __always_inline__, __used__))
inline t_xft_sysres	xft_statx(const char *restrict path, t_u32a flags,
		t_u32a mask, t_statx *statxbuf)
{
	t_ssize	ret;
	t_u64a	r;

	ret = syscall(SYS_statx, xft_at_fdcwd, path, flags, mask, statxbuf);
	r = xft_tern(errno == EINTR || errno == EAGAIN, xft_sys_repeat, xft_sys_ko);
	r = xft_tern(ret < 0, r, xft_sys_ok);
	return ((t_xft_sysres)r);
}

# endif

#endif
