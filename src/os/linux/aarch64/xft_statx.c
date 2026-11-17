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

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1, 4), __always_inline__, __used__))
inline t_xft_sysres	xft_statx(const char *restrict path, t_u32a flags,
		t_u32a mask, t_statx *statxbuf)
{
	t_u64a	args[6];
	t_i64a	ret;
	t_u64a	r;

	args[0] = (t_u64a)xft_at_fdcwd;
	args[1] = (t_u64a)path;
	args[2] = flags;
	args[3] = mask;
	args[4] = (t_u64a)statxbuf;
	args[5] = 0;
	ret = xft_syscall6(xft_sys_statx, args);
	r = xft_tern(ret < 0, xft_sys_ko, xft_sys_ok);
	r = xft_tern(ret == -xft_eintr || ret == -xft_eagain, xft_sys_repeat, r);
	return ((t_xft_sysres)r);
}

# endif

#endif
