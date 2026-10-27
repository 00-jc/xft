/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline t_any	xft_fmap(t_size size, t_u64a prot, t_u64a flags, int fd)
{
	t_u64a	args[6];

	args[0] = 0;
	args[1] = (t_u64a)size;
	args[2] = prot;
	args[3] = flags;
	args[4] = fd;
	args[5] = 0;
	return ((t_any)xft_syscall6(xft_sys_mmap, args));
}

# endif

#endif
