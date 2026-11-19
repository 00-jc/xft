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

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1, 4), __always_inline__, __used__))
inline t_result	xft_statx(const char *restrict path, t_u32a flags,
		t_u32a mask, t_statx *statxbuf)
{
	int					ret;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");

	r10 = mask;
	r8 = (long)statxbuf;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_statx),
		"D"((long)xft_at_fdcwd),
		"S"(path),
		"d"((long)flags),
		"r"(r10), "r"(r8)
		: "rcx", "r11", "memory"
	);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

# endif

#endif
